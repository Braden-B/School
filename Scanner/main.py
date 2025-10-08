import regexTokenizer as tk
from more_itertools import peekable
from RegexParser import RegexParser

inputs = ['two', 't|w|o', '[two]', "[ˆtwo]", "t(oo?|wo)", "(<(/?[ˆ>]+)\>)"]
for regex in inputs:
    print(f'Processing expression"{regex}"')
    tokens = peekable(tk.tokenize(regex))
    parser = RegexParser(tokens)
    parser.parse_re(0)