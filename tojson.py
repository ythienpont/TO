f = open("wordlist.json", "w")

f.write("{\n\t\"epsilon\": \"%\",\n\t\"wordlist\": [\n")

with open('wordlist.txt','r') as file:
   
    # reading each line    
    for line in file:
   
        # reading each word        
        for word in line.split():
            add = True
            for letter in word:
                theOrd = ord(letter)
                if theOrd < 65 or theOrd > 123:
                    add = False
  
            if add == True:
                # displaying the words
                f.write("\t\t\"")
                f.write(word)
                f.write("\",\n")

f.write("\t\t\"einde\"\n")
f.write("\t]\n}")
