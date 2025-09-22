# Mastermind Game

A classic code-breaking game where you attempt to guess a secret 4-digit code within a limited number of attempts.

## How to Build

```bash
make
```

## How to Play

### Basic Usage
```bash
./game
```

### Rules
- The secret code is 4 digits long using numbers 0-8
- Each digit appears only once (no duplicates)
- You have 10 attempts to guess correctly
- After each guess, you get feedback:
  - **Well placed pieces**: Correct digits in correct positions
  - **Misplaced pieces**: Correct digits in wrong positions

### Example Gameplay
```
> 1234
Well placed pieces: 1
Misplaced pieces: 2
---
Round 1
> 0321
Well placed pieces: 2
Misplaced pieces: 1
---
Round 2
```

## Command Line Options

```bash
./game -t 15        # Change attempts to 15
./game -c 1234      # Set custom secret code
./game -t 8 -c 5678 # 8 attempts with specific code
```

## Code Requirements

### Valid Examples
- `1234` - Four unique digits 0-8
- `0578` - Can start with 0
- `8321` - Any order is fine

### Invalid Examples
- `1233` - Contains duplicate digit
- `123` - Too short
- `12345` - Too long  
- `1239` - Contains invalid digit (9)

## Strategy Tips

1. Start with diverse digits like `0123` to test multiple numbers
2. Use feedback to eliminate possibilities
3. Track which digits are confirmed in/out of the code
4. Work on positioning once you know the digits

Good luck breaking the code!
