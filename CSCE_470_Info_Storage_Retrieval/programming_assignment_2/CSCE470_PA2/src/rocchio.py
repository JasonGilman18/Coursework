from data import Dataset, Labels
from utils import evaluate
import math
import os, sys
import time


class Rocchio:
	def __init__(self):
		# centroids vectors for each Label in the training set.
		self.centroids = {l: {} for l in Labels}

	def train(self, ds):
		"""
		ds: list of (id, x, y) where id corresponds to document file name,
		x is a string for the email document and y is the label.

		TODO: Loop over all the samples in the training set, convert the
		documents to vectors and find the centroid for each Label.
		"""

		#create raw term freq and normalize for each doc, classify for the label
		normalized_doc_vectors = {l: [] for l in Labels}
		for document in ds:
			doc_string = document[1].lower()
			doc_label = document[2]

			raw_freqs = {}
			for word in doc_string.split():
				freq = doc_string.count(" " + word + " ")
				raw_freqs[word] = freq
				
			norm_sum = 0.0
			for word in raw_freqs:
				freq = raw_freqs[word]
				norm_sum += math.pow(freq, 2)

			norm_val = math.sqrt(norm_sum)
			for word in raw_freqs:
				raw_freqs[word] /= norm_val

			normalized_doc_vectors[doc_label].append(raw_freqs.copy())
			raw_freqs.clear()

		#sum normalized freq for each label and create centroid
		for label in normalized_doc_vectors:
			num_docs_in_label = len(normalized_doc_vectors[label])
			centroid_vector = {word: 0.0 for normalized_doc_vector in normalized_doc_vectors[label] for word in normalized_doc_vector}
			for normalized_doc_vector in normalized_doc_vectors[label]:
				for word in normalized_doc_vector:
					centroid_vector[word] += normalized_doc_vector[word]
			
			for word in centroid_vector:
				centroid_vector[word] /= num_docs_in_label

			self.centroids[label] = centroid_vector.copy()
			centroid_vector.clear()
						



	def predict(self, x):
		"""
		x: string of words in the document.
		
		TODO: Convert x to vector, find the closest centroid and return the
		label corresponding to the closest centroid.
		"""

		#create raw freq and normalize for input
		input_vector = {}
		input_string = x.lower()
		for word in input_string.split():
			input_vector[word] = input_string.count(" " + word + " ")
		
		norm_sum = 0.0
		for word in input_vector:
			freq = input_vector[word]
			norm_sum += math.pow(freq, 2)

		norm_val = math.sqrt(norm_sum)
		input_vector_mag = 0.0
		for word in input_vector:
			input_vector[word] /= norm_val
			input_vector_mag += math.pow(input_vector[word], 2)

		input_vector_mag = math.sqrt(input_vector_mag)

		#compute cosine similarity between centroid and input vectors
		similarities = []
		for label in self.centroids:
			centroid_vector = self.centroids[label]
			common_words = input_vector.keys() & centroid_vector.keys()
			
			centroid_vector_mag = 0.0
			for word in centroid_vector:
				centroid_vector_mag += math.pow(centroid_vector[word], 2)

			centroid_vector_mag = math.sqrt(centroid_vector_mag)
				
			dot_product = 0.0
			for word in common_words:
				dot_product += input_vector[word] * centroid_vector[word]

			similarity_score = dot_product / (input_vector_mag * centroid_vector_mag)
			similarities.append({"label": label, "similarity": similarity_score})
		
		sorted_similarities = sorted(similarities, key=lambda i: i["similarity"], reverse=True)
		
		return sorted_similarities[0]["label"]
			




def main(train_split):
	rocchio = Rocchio()
	ds = Dataset(train_split).fetch()
	val_ds = Dataset('val').fetch()
	
	
	
	rocchio.train(ds)



	# Evaluate the trained model on training data set.
	print('-'*20 + ' TRAIN ' + '-'*20)
	evaluate(rocchio, ds)
	# Evaluate the trained model on validation data set.
	print('-'*20 + ' VAL ' + '-'*20)
	evaluate(rocchio, val_ds)

	# students should ignore this part.
	# test dataset is not public.
	# only used by the grader.
	if 'GRADING' in os.environ:
		print('\n' + '-'*20 + ' TEST ' + '-'*20)
		test_ds = Dataset('test').fetch()
		evaluate(rocchio, test_ds)

if __name__ == "__main__":
	train_split = 'train'
	if len(sys.argv) > 1 and sys.argv[1] == 'train_half':
		train_split = 'train_half'
	main(train_split)
