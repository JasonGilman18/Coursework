package scorer;

import ds.Document;
import ds.Query;
import utils.IndexUtils;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Map;

/**
 * Skeleton code for the implementation of a
 * Cosine Similarity scorer in Task 1.
 */
public class VSMScorer extends AScorer {

    /*
     * TODO: You will want to tune the values for
     * the weights for each field.
     */
    double titleweight  = 0.3;
    double bodyweight = 0.6;


    /**
     * Construct a Cosine Similarity scorer.
     * @param utils Index utilities to get term/doc frequencies
     */
    public VSMScorer(IndexUtils utils) {
        super(utils);
    }

    /**
     * Get the net score for a query and a document.
     * @param tfs the term frequencies
     * @param q the ds.Query
     * @param tfQuery the term frequencies for the query
     * @param d the ds.Document
     * @return the net score
     */
    public double getNetScore(Map<String, Map<String, Double>> tfs, Query q, Map<String,Double> tfQuery, Document d) {
        double score = 0.0;

        /*
         * TODO : Your code here
         * See Equation 1 in the handout regarding the net score
         * between a query vector and the term score vectors
         * for a document.
         */
        
        // for each term do tfs * tfQuery and sum it

        int numQueryWords = q.queryWords.size();
        String queryTerm;
        double queryFreq;
        double titleFreq;
        double bodyFreq;
        for(int i=0;i<numQueryWords;i++)
        {
            queryTerm = q.queryWords.get(i).toLowerCase();
            queryFreq = tfQuery.get(queryTerm);
            titleFreq = tfs.get("title").get(queryTerm);
            bodyFreq = tfs.get("body").get(queryTerm);
            score += queryFreq*(titleweight*titleFreq + bodyweight*bodyFreq);
        }
        return score;
    }

    /**
     * Normalize the term frequencies.
     * @param tfs the term frequencies
     * @param d the ds.Document
     * @param q the ds.Query
     */
    public void normalizeTFs(Map<String,Map<String, Double>> tfs, Document d, Query q) {
        /*
         * TODO : Your code here
         * Note that we should use the length of each field 
         * for term frequency normalization as discussed in the assignment handout.
         */

        int titleLength = d.title_length;
        double titleFreq;
        int bodyLength = d.body_length;
        double bodyFreq;
        int queryLength = q.queryWords.size();
        String queryTerm;
        for(int i=0;i<queryLength;i++)
        {
            queryTerm = q.queryWords.get(i);
            titleFreq = tfs.get("title").get(queryTerm);
            bodyFreq = tfs.get("body").get(queryTerm);

            titleFreq /= titleLength;
            bodyFreq /= bodyLength;
            tfs.get("title").put(queryTerm, titleFreq);
            tfs.get("body").put(queryTerm, bodyFreq);
        }
    }

    /**
     * Write the tuned parameters of vsmSimilarity to file.
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
                    "titleweight", "bodyweight"
            };
            double[] values = {
                    this.titleweight, this.bodyweight
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
    /** Get the similarity score between a document and a query.
     * @param d the ds.Document
     * @param q the ds.Query
     * @return the similarity score.
     */
    public double getSimScore(Document d, Query q) {
        Map<String,Map<String, Double>> tfs = this.getDocTermFreqs(d,q);
        this.normalizeTFs(tfs, d, q);
        Map<String,Double> tfQuery = getQueryFreqs(q);

        // Write out tuned vsmSimilarity parameters
        // This is only used for grading purposes.
        // You should NOT modify the writeParaValues method.
        writeParaValues("vsmPara.txt");
        return getNetScore(tfs,q,tfQuery,d);
    }
}