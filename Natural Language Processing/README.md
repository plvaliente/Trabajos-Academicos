## Generar files

1) Bajar los .json y .csv de la data de Kaggle (https://www.kaggle.com/c/eci2019nlp/data)
2) Correr 'python3 read_data.py snli_1.0_train_filtered.jsonl snli_1.0_train_gold_labels.csv' para generar el archivo de entrenamiento 'fast.txt'
3) Correr 'python3 read_data.py snli_1.0_train_filtered.jsonl snli_1.0_train_gold_labels.csv' para generar el archivo de dev para chequear resultados
4) Correr 'python3 read_data_dev.py snli_1.0_test_filtered.jsonl' para generar el archivo de test

La notebook tiene un modelo de fasttext, entrena con los files de training, chequea contra dev y deja los resultados de test.
