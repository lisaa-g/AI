from collections import Counter
import numpy as np

plays = {
    "The Merchant of Venice": "merchant.txt",
    "Romeo and Juliet": "romeo.txt",
    "The Tempest": "tempest.txt",
    "Twelfth Night": "twelfth.txt",
    "Othello": "othello.txt",
    "King Lear": "lear.txt",
    "Much Ado About Nothing": "ado.txt",
    "Midsummer Night’s Dream": "midsummer.txt",
    "Macbeth": "macbeth.txt",
    "Hamlet": "hamlet.txt"
}

#function that removes special characters and makes everything lower case
def clean_words(text):
    words = []
    current_word = ''
    
    for char in text:
        if char.isalpha() or char.isspace():
            if char.isalpha():
                current_word += char.lower()
            elif current_word:
                words.append(current_word)
                current_word = '' 
        elif char == '\n':
            if current_word:
                words.append(current_word)
                current_word = '' 

    if current_word:
        words.append(current_word)

    return words

#function that counts how many times each word appears
def word_counter(filename):
    all_words = []

    with open(filename, 'r', encoding='utf-8') as file:
        for line in file:
            words = clean_words(line)
            all_words.extend(words)

    word_freq = Counter(all_words)
    return word_freq


#function that calculates the probability
def probability(words: list, prior: float, plays):
    probs = {}
    total_words = {}
    for play, freq in plays.items():
        total_words[play] = sum(freq.values())

    for play, freq in plays.items():
        prob = np.log(prior)
        for word in words:
            if word in freq:
                prob = prob + np.log(freq[word] / total_words[play])
            else:
                prob = prob + np.log(1 / 1e6)
        probs[play] = prob

    return probs

#function that determines the best play
def best_play(prob):
    best_play = max(prob, key=prob.get)
    return best_play


sentence = input()
words = clean_words(sentence)
prior = 1 / len(plays)
word_freqs = {}
for play, file_name in plays.items():
    word_freqs[play] = word_counter(file_name)
prob = probability(words, prior, word_freqs)
play = best_play(prob)
print(play)