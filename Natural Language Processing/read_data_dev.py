#!/usr/bin/env python
import argparse
import json
import csv

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('sentences')
    ap.add_argument('labels', nargs='?')

    args = ap.parse_args()
    sentence_data = open(args.sentences, 'r')
    if args.labels:
        fasttext_output = open("fast_dev.csv", "w+")
        fasttext_output.write("label,sentence\n")
        label_data = open(args.labels, 'r')
        for sentence, label in zip(it_sentences(sentence_data), it_labels(label_data)):
        	fasttext_output.write(("%s,%s\n" % (label, sentence)))
            # Tenemos la oración en sentence con su categoría en label
            #print(label, sentence)
    else:
        fasttext_output = open("fast_test.csv", "w+")
        for sentence in it_sentences(sentence_data):
            fasttext_output.write("%s\n" % sentence)
            # Tenemos una oración en sentence
            #print(sentence)
            pass
    

def it_sentences(sentence_data):
    for line in sentence_data:
        example = json.loads(line)
        yield example['sentence2']

def it_labels(label_data):
    label_data_reader = csv.DictReader(label_data)
    for example in label_data_reader:
        yield example['gold_label']




main()
