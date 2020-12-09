package scorer;

import ds.Document;
import ds.Query;
import utils.IndexUtils;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Spliterators.AbstractLongSpliterator;

/**
 * Skeleton code for the implementation of a BM25 scorer in Task 2.
 */
public class BM25Scorer extends AScorer {

    /*
     *  TODO: You will want to tune these values
     */
    double titleweight  = 0.9;
    double bodyweight = 0.1;

    // BM25-specific weights
    double btitle = 0.9;
    double bbody = 0.1;

    double k1 = 10;
    double pageRankLambda = 0.9;
    double pageRankLambdaPrime = 0.9;

    // query -> url -> document
    Map<Query,Map<String, Document>> queryDict;

    // BM25 data structures--feel free to modify these
    // ds.Document -> field -> length
    Map<Document,Map<String,Double>> lengths;

    // field name -> average length
    Map<String,Double> avgLengths;

    // ds.Document -> pagerank score
    Map<Document,Double> pagerankScores;

    /**
     * Construct a scorer.BM25Scorer.
     * @param utils Index utilities
     * @param queryDict a map of query to url to document
     */
    public BM25Scorer(IndexUtils utils, Map<Query,Map<String, Document>> queryDict) {
        super(utils);
        this.queryDict = queryDict;
        this.calcAverageLengths();
    }

    /**
     * Set up average lengths for BM25, also handling PageRank.
     */
    public void calcAverageLengths() {
        lengths = new HashMap<>();
        Map<String, Double> innerLengths = new HashMap<>();
        avgLengths = new HashMap<>(); 
        pagerankScores = new HashMap<>();

        /*
         * TODO : Your code here
         * Initialize any data structures needed, perform
         * any preprocessing you would like to do on the fields,
         * accumulate lengths of fields.
         * handle pagerank.  
         */

        double avgTitleLength = 0;
        double avgBodyLength = 0;
        int docCount = 0;
        for(Map<String, Document> url : queryDict.values())
        {
            for(Document doc: url.values())
            {
                innerLengths.put("title", (double)doc.title_length);
                innerLengths.put("body", (double)doc.body_length);
                avgTitleLength += doc.title_length;
                avgBodyLength += doc.body_length;
                lengths.put(doc,innerLengths);
                pagerankScores.put(doc, (double)doc.page_rank);
                docCount ++;
            }
        }

        //storing the avgs - normalization will take place in normalizeTFS
        avgLengths.put("title", avgTitleLength/docCount);
        avgLengths.put("body", avgBodyLength/docCount);

        /*
        for (String tfType : this.TFTYPES) {
            
             * TODO : Your code here
             * Normalize lengths to get average lengths for
             * each field (body, title).
        }
        */
    }

    /**
     * Get the net score.
     * @param tfs the term frequencies
     * @param q the ds.Query
     * @param tfQuery
     * @param d the ds.Document
     * @return the net score
     */
    public double getNetScore(Map<String,Map<String, Double>> tfs, Query q, Map<String,Double> tfQuery, Document d) {

        double score = 0.0;

        /*
         * TODO : Your code here
         * Use equation 3 first and then equation 4 in the writeup to compute the overall score
         * of a document d for a query q.
         */

        int numQueryWords = q.queryWords.size();
        String queryTerm;
        double queryTF;
        double titleTF;
        double bodyTF;
        double ovrWeight;
        for(int i=0;i<numQueryWords;i++)
        {
            queryTerm = q.queryWords.get(i);
            titleTF = tfs.get("title").get(queryTerm);
            bodyTF = tfs.get("body").get(queryTerm);
            queryTF = tfQuery.get(queryTerm);
            ovrWeight = (titleweight*titleTF) + (bodyweight*bodyTF);
            score += (ovrWeight/(k1+ovrWeight)) + pageRankLambda*(Math.log(pageRankLambdaPrime + d.page_rank));
        }
        return score;
    }

    /**
     * Do BM25 Normalization.
     * @param tfs the term frequencies
     * @param d the ds.Document
     * @param q the ds.Query
     */
    public void normalizeTFs(Map<String,Map<String, Double>> tfs, Document d, Query q) {
        /*
         * TODO : Your code here
         * Use equation 2 in the writeup to normalize the raw term frequencies
         * in fields in document d.
         */

        Map<String, Double> qVal;
        double bVal;
        double termTF;
        double length;
        double avgLength;
        for(String field : tfs.keySet())
        {
            qVal = tfs.get(field);
            if(field.equals("title"))
            {
                bVal = btitle;
                avgLength = avgLengths.get("title");
                length = d.title_length;
            }
            else
            {
                bVal = bbody;
                avgLength = avgLengths.get("body");
                length = d.body_length;
            }

            for(String queryTerm : qVal.keySet())
            {
                termTF = qVal.get(queryTerm);
                termTF = termTF / ((1-bVal) + bVal*(length/avgLength));
                qVal.put(queryTerm, termTF);
            }
        }
        
    }

    /**
     * Write the tuned parameters of BM25 to file.
     * Only used for grading purpose, you should NOT modify this method.
     * @param filePath the output file path.
     */
    private void writeParaValues(String filePath) {
        try {
            File file = new File(filePath);
            if (!file.exists()) {
                file.createNewFile();
            }
            FileWriter fw = new FileWriter(file.getAbsoluteFile());
            String[] names = {
                    "titleweight", "bodyweight", "btitle",
                    "bbody", "k1", "pageRankLambda", "pageRankLambdaPrime"
            };
            double[] values = {
                    this.titleweight, this.bodyweight, this.btitle,
                    this.bbody, this.k1, this.pageRankLambda,
                    this.pageRankLambdaPrime
            };
            BufferedWriter bw = new BufferedWriter(fw);
            for (int idx = 0; idx < names.length; ++ idx) {
                bw.write(names[idx] + " " + values[idx]);
                bw.newLine();
            }
            bw.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    /**
     * Get the similarity score.
     * @param d the ds.Document
     * @param q the ds.Query
     * @return the similarity score
     */
    public double getSimScore(Document d, Query q) {
        Map<String,Map<String, Double>> tfs = this.getDocTermFreqs(d,q);
        this.normalizeTFs(tfs, d, q);
        Map<String,Double> tfQuery = getQueryFreqs(q);

        // Write out the tuned BM25 parameters
        // This is only used for grading purposes.
        // You should NOT modify the writeParaValues method.
        writeParaValues("bm25Para.txt");
        return getNetScore(tfs,q,tfQuery,d);
    }

}
