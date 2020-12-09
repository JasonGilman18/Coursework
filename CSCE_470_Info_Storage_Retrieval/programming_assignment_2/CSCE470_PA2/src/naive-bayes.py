from data import Dataset, Labels
from utils import evaluate
import math
import os, sys
import time

class NaiveBayes:
	def __init__(self):
		# total number of documents in the training set.
		self.n_doc_total = 0
		# total number of documents for each label/class in the trainin set.
		self.n_doc = {l: 0 for l in Labels}
		# frequency of words for each label in the trainng set.
		self.vocab = {l: {} for l in Labels}

	def train(self, ds):
		"""
		ds: list of (id, x, y) where id corresponds to document file name,
		x is a string for the email document and y is the label.

		TODO: Loop over the dataset (ds) and update self.n_doc_total,
		self.n_doc and self.vocab.
		"""

		labelStrings = {l: "" for l in Labels}

		#create big strings containing all docs for a label
		#and assign values to class variables
		self.n_doc_total = len(ds)
		for document in ds:
			doc_string = document[1].lower()
			doc_label = document[2]
			self.n_doc[doc_label] += 1
			labelStrings[doc_label] += doc_string

		#create word freqs and add them to class dict for each label
		for label in labelStrings:
			label_string = labelStrings[label]
			for word in label_string.split():
				self.vocab[label][word] = label_string.count(" " + word + " ")

		


	def predict(self, x):
		"""
		x: string of words in the document.
		
		TODO: Use self.n_doc_total, self.n_doc and self.vocab to calculate the
		prior and likelihood probabilities.
		Add the log of prior and likelihood probabilities.
		Use MAP estimation to return the Label with hight score as
		the predicted label.
		"""

		labelVals = {l: 0.0 for l in Labels}
		input_string = x.lower()

		for label in self.vocab:
			prior = math.log((self.n_doc[label] + 1)/(self.n_doc_total + 1))
			sum_cond = 0.0
			for word in input_string.split():
				tempWords = self.vocab[label]
				sumFreq = sum(tempWords.values())
				word_freq = 0
				if word in self.vocab[label]:
					word_freq = self.vocab[label][word]
				sum_cond += math.log((word_freq + 1)/(sumFreq + self.n_doc[label] + 1))
			labelVals[label] = prior + sum_cond

		return max(labelVals, key=labelVals.get)




def main(train_split):
	nb = NaiveBayes()
	ds = Dataset(train_split).fetch()
	val_ds = Dataset('val').fetch()
	

	nb.train(ds)





	# Evaluate the trained model on training data set.
	print('-'*20 + ' TRAIN ' + '-'*20)
	evaluate(nb, ds)
	# Evaluate the trained model on validation data set.
	print('-'*20 + ' VAL ' + '-'*20)
	evaluate(nb, val_ds)

	# students should ignore this part.
	# test dataset is not public.
	# only used by the grader.
	if 'GRADING' in os.environ:
		print('\n' + '-'*20 + ' TEST ' + '-'*20)
		test_ds = Dataset('test').fetch()
		evaluate(nb, test_ds)
	


if __name__ == "__main__":
	train_split = 'train'
	if len(sys.argv) > 1 and sys.argv[1] == 'train_half':
		train_split = 'train_half'
	main(train_split)
