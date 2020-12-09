package scorer;

import ds.Document;
import ds.Query;
import utils.IndexUtils;

import java.util.HashMap;
import java.util.Map;
import java.lang.Math;
import java.util.List;

/**
 * An abstract class for a scorer.
 * Needs to be extended by each specific implementation of scorers.
 */
public abstract class AScorer {

    // Map: term -> idf
    IndexUtils utils;

    // Various types of term frequencies that you will need
    String[] TFTYPES = {"title","body"};

    /**
     * Construct an abstract scorer with a map of idfs.
     * @param utils index utility functions like map of idf scores
     */
    public AScorer(IndexUtils utils) {
        this.utils = utils;
    }

    /**
     * You can implement your own function to whatever you want for debug string
     * The following is just an example to include page information in the debug string
     * The string will be forced to be 1-line and truncated to only include the first 200 characters
     */
    public String getDebugStr(Document d, Query q)
    {
        return "Pagerank: " + Integer.toString(d.page_rank);
    }

    /**
     * Score each document for each query.
     * @param d the ds.Document
     * @param q the ds.Query
     */
    public abstract double getSimScore(Document d, Query q);

    /**
     * Get frequencies for a query.
     * @param q the query to compute frequencies for
     */
    public Map<String,Double> getQueryFreqs(Query q) {

        // queryWord -> term frequency
        Map<String,Double> tfQuery = new HashMap<>();

        /*
         * TODO : Your code here
         * Compute the raw term frequencies
         * Additionally weight each of the terms using the idf value
         * of the term in the query (we use the provided text corpus to 
         * determine how many documents contain the query terms, which is stored
         * in this.idfs).
         */

        int queryLength = q.queryWords.size();
        String queryTerm = "";
        double idf = 0;
        for(int i=0;i<queryLength;i++)
        {
            queryTerm = (q.queryWords.get(i)).toLowerCase();
            idf = 1 + Math.log(this.utils.totalNumDocs()/(double)this.utils.docFreq(queryTerm));
            //idf = this.utils.totalNumDocs()/(double)this.utils.docFreq(queryTerm);
            tfQuery.put(queryTerm, idf);
        }

        return tfQuery;
    }


    /*
     * TODO (Optional in case you want to do any preprocessing here) : Your code here
     * Include any initialization and/or parsing methods
     * that you may want to perform on the ds.Document fields
     * prior to accumulating counts.
     * See the ds.Document class in ds.Document.java to see how
     * the various fields are represented.
     */


    /**
     * Accumulate the various kinds of term frequencies
     * for the fields (title, body).
     * You can override this if you'd like, but it's likely
     * that your concrete classes will share this implementation.
     * @param d the ds.Document
     * @param q the ds.Query
     */
    public Map<String,Map<String, Double>> getDocTermFreqs(Document d, Query q) {

        // Map from tf type (field) -> queryWord -> score
        Map<String,Map<String, Double>> tfs = new HashMap<>();
        Map<String, Double> innerTitle = new HashMap<>();
        Map<String, Double> innerBody = new HashMap<>();

        double tfTitle = 0;
        String splitTitle[] = d.title.split(" ");

        double tfBody = 0;
        Map<String, List<Integer>> body = d.body_hits;

        String lower = "";

        for (String queryWord : q.queryWords) {
            /*
             * TODO: Your code here
             * Loop through query terms and accumulate term frequencies.
             * Note: you should do this for each type of term frequencies,
             * i.e. for each of the different fields.
             * Don't forget to lowercase the query word.
             */

            //find the count of lower in body, then divide by num words in that, then store in map
            //find count of lower in title, then divide by num words in that, then store in map

            lower = queryWord.toLowerCase();
            
            for(int i=0;i<splitTitle.length;i++)
            {
                if(lower.equals(splitTitle[i].toLowerCase()))
                    tfTitle ++;
            }
            innerTitle.put(lower, tfTitle);

            if(body != null)
            {
                //produces .8627
                for(String term:body.keySet())
                {
                    if(term.equals(lower))
                    {
                        tfBody += body.get(lower).size();
                    }
                }
                
                //produces .8620
                /*
                if(body.containsKey(lower))
                    tfBody = body.get(lower).size();

                */
            }
            innerBody.put(lower, tfBody);
        }
        tfs.put(TFTYPES[0], innerTitle);
        tfs.put(TFTYPES[1], innerBody);

        return tfs;
    }

}