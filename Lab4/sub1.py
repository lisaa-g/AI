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


input_text = input()
output_text = clean_words(input_text)
print(output_text)
