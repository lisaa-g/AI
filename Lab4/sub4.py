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
    "Midsummer Night's Dream": "midsummer.txt",
    "Macbeth": "macbeth.txt",
    "Hamlet": "hamlet.txt"
}

#function that removes special characters and makes everything lowercase
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

#function that calculates the probabilities
def probabilities(words, plays):
    probs = {}
    total_words = {}
    for play, filename in plays.items():
        freq = word_counter(filename)
        total_words[play] = sum(freq.values())

        prob = 0
        for word in words:
            if word in freq:
                prob = prob + np.log(freq[word] / total_words[play])
            else:
                prob = prob + np.log(1 / 1e6)
        probs[play] = prob

    return probs

#function that calculates the full posterior probabilities
def full_posterior(words, plays):
    probs = probabilities(words, plays)
    max_prob = max(probs.values())
    prob_sum = 0

    for play, log_prob in probs.items():
        prob_sum = prob_sum + np.exp(log_prob - max_prob)

    posterior_probs = {}
    for play, log_prob in probs.items():
        posterior_probs[play] = np.exp(log_prob - max_prob) / prob_sum

    return posterior_probs



sentence = input()
words = clean_words(sentence)
posterior_probs = full_posterior(words, plays)
sorted_probs = sorted(posterior_probs.items(), key=lambda x: x[1], reverse=True)

with open("output.txt", "w") as file:
    for play, prob in sorted_probs:
        file.write(f"{play}: {round(prob * 100)}%\n")