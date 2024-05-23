from collections import Counter

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

    return ' '.join(words)



filename = input()
all_words = []

#read from the file
with open(filename, 'r', encoding='utf-8') as file:
    for line in file:
        words = line.split()
        cleaned_words = [clean_words(word) for word in words]
        all_words.extend(cleaned_words)

#count the frequency of each word
word_freq = Counter(all_words)
#get the top three most common words
top_three_words = word_freq.most_common(3)

print(' '.join(word for word, _ in top_three_words))