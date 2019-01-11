import re

def tokenizer(string, status=0):
    tokens = re.findall("[A-Z]{2,}(?![a-z])|[A-Za-z]+(?=[A-Z])|[\'\w\-]+", string)
    if status:
        print("{}\nstring: {}\nTokens: {}".format("=*"*20, string, tokens))


if __name__ == "__main__":
    sample_code = """void main(){
        int i=0;
        char
        printf("Hello, World!");
    }
    """
    tokenizer("Hello, Jarvis! How are you?", 1)
    tokenizer(sample_code, 1)
    tokenizer(input("Enter String: "), 1)