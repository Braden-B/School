from more_itertools import peekable

class RegexParser:
    tokens = peekable([])
    lookaheadHolder = ''
    def __init__(self, tokens):
        self.tokens = tokens
        self.lookaheadHolder = '['
    def peek(self):
        return self.tokens.peek()
    def next(self):
        return self.tokens.next()

    def parse_re(self, level):
        if level == 0:
            print("RE")
            return self.parse_re(1)
        if level == 1:
            if self.tokens.peek().value == '|':
                print("    " + self.tokens.peek().value + " " + self.tokens.next().type)
            print("    S_RE")
            return self.parse_re(2)
        if level == 2:
            print("        B_RE")
            return self.parse_re(3)
        if level == 3:
            if self.tokens.peek().value == '*' or self.tokens.peek().value == '+' or self.tokens.peek().value == '?':
                print("    " + self.tokens.peek().value + " " + self.tokens.next().type)
            print("            E_RE")
            return self.parse_re(4)
        if level == 4:
            if self.tokens.peek().value == '(':
                print("            " + self.tokens.peek().value + " " + self.tokens.next().type)
                return self.parse_re(1)
            if self.tokens.peek().value == ')':
                print("            " + self.tokens.peek().value + " " + self.tokens.next().type)
            if self.tokens.peek().value == '.':
                print("            " + self.tokens.peek().value + " " + self.tokens.next().type)
            if self.tokens.peek().kind == "CHAR":
                print("                CHAR_OR_META")
                return self.parse_re(5)
            if self.tokens.peek().value == "[":
                self.tokens.next()
                if self.tokens.peek().value == '^':
                    print("    " + self.lookaheadHolder + self.tokens.next().value)
                else:
                    print("    " + self.tokens.next().value)
                print("                SET_ITEMS")
                return self.parse_re(6)
            if self.tokens.peek().value == "]":
                print("    " + self.tokens.next().value)
        if level == 5:
            print("                    " + self.tokens.peek().value + " " + self.tokens.next().type)
        if (level == 6):
            return self.parse_re(6)