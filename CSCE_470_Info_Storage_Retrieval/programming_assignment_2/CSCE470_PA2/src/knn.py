from data import Dataset, Labels
from utils import evaluate
import os, sys
import math
import time
from collections import Counter

K = 5

class KNN:
	def __init__(self):
		# bag of words document vectors
		self.bow = []

	def train(self, ds):
		"""
		ds: list of (id, x, y) where id corresponds to document file name,
		x is a string for the email document and y is the label.

		TODO: Save all the documents in the train dataset (ds) in self.bow.
		You need to transform the documents into vector space before saving
		in self.bow.
		"""

		#get raw term freqs and store it with label relevance
		for document in ds:
			doc_string = document[1].lower()
			doc_label = document[2]

			raw_freq = {}
			for word in doc_string.split():
				raw_freq[word] = doc_string.count(" " + word + " ")
			
			self.bow.append({doc_label: raw_freq.copy()})
			raw_freq.clear()
		



	def predict(self, x):
		"""
		x: string of words in the document.

		TODO: Predict class for x.
		1. Transform x to vector space.
		2. Find k nearest neighbors.
		3. Return the class which is most common in the neighbors.
		"""
		
		#get raw term freq for the input
		input_string = x.lower()
		input_vector = {}
		for word in input_string.split():
			input_vector[word] = input_string.count(" " + word + " ")

		input_mag = 0.0
		for word in input_vector:
			freq = input_vector[word]
			input_mag += math.pow(freq, 2)

		input_mag = math.sqrt(input_mag)


		#compute cosine similarity		
		similarities = []
		for doc in self.bow:
			doc_label = list(doc.keys())[0]
			doc_vector = list(doc.values())[0]

			doc_mag = 0.0
			for word in doc_vector:
				freq = doc_vector[word]
				doc_mag += math.pow(freq, 2)

			doc_mag = math.sqrt(doc_mag)

			common_words = doc_vector.keys() & input_vector.keys()
			
			dot_product = 0.0
			for word in common_words:
				dot_product += doc_vector[word] * input_vector[word]

			similarity_score = dot_product / (input_mag * doc_mag)
			similarities.append({"label": doc_label, "similarity": similarity_score})


		#order similarities and get top K docs
		sorted_similarties = sorted(similarities, key = lambda i: i['similarity'], reverse=True)
		findMax = {l: 0.0 for l in Labels}
		for i in range(K):
			findMax[sorted_similarties[i]["label"]] += sorted_similarties[i]["similarity"]

		return max(findMax, key=findMax.get)
		



def main(train_split):
	knn = KNN()
	ds = Dataset(train_split).fetch()
	val_ds = Dataset('val').fetch()



	knn.train(ds)




	# Evaluate the trained model on training data set.
	print('-'*20 + ' TRAIN ' + '-'*20)
	evaluate(knn, ds)
	# Evaluate the trained model on validation data set.
	print('-'*20 + ' VAL ' + '-'*20)
	evaluate(knn, val_ds)

	# students should ignore this part.
	# test dataset is not public.
	# only used by the grader.
	if 'GRADING' in os.environ:
		print('\n' + '-'*20 + ' TEST ' + '-'*20)
		test_ds = Dataset('test').fetch()
		evaluate(knn, test_ds)


if __name__ == "__main__":
	train_split = 'train'
	if len(sys.argv) > 1 and sys.argv[1] == 'train_half':
		train_split = 'train_half'
	main(train_split)
