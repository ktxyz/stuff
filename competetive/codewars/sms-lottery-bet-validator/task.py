import re

def validate_bet(game, text):
    try:
        numbers = [int(x) for x in re.findall(r'\d+|[^\d\s,]+', text)]
        if len(numbers) != game[0] or len(set(numbers)) != len(numbers):
            return None
        if any(num < 1 or num > game[1] for num in numbers):
            return None
        return sorted(set(numbers))
    except ValueError:
        return None
