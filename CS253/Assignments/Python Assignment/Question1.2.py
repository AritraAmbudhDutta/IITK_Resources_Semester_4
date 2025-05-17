# This program implements a simple Rock, Paper, Scissors game
# The user plays against the computer, which makes random choices
# The program keeps track of scores and allows multiple rounds of play

import random
player_score, computer_score, ties = 0, 0, 0  # Initialize game scores

def map(computer):
    """
    Maps the computer's numeric choice (0, 1, 2) to a string representation
    Args:
        computer: Integer representing computer's choice (0, 1, or 2)
    Returns:
        String representation of the computer's choice
    """
    if computer == 0:
        return "Rock"
    elif computer == 1:
        return "Paper"
    else:
        return "Scissors"

def Whoiswinner():
    """
    Main game loop that:
    1. Gets user input for their choice
    2. Generates computer's random choice
    3. Determines the winner based on game rules
    4. Updates and displays scores
    5. Continues until user quits
    """
    global player_score, computer_score, ties
    while True:
        player_choice = input("Type 'Quit' to exit. Otherwise enter your choice (Rock, Paper, Scissors): ").strip().lower()
        if player_choice == "quit": 
            print("Thanks for playing!")
            break
        elif player_choice not in ["rock", "paper", "scissors"]:
            print("Invalid choice. Please try again.")
            continue

        player_choice = player_choice.capitalize()
        computer = random.randint(0, 2)  # Generate random choice for computer (0, 1, or 2)
        computer_choice = map(computer)
        print(f"You chose: {player_choice}")
        print(f"Computer chose: {computer_choice}")

        # Determine winner according to game rules
        if player_choice == computer_choice:
            ties += 1
            print("It's a tie!")
        elif (player_choice == "Rock" and computer_choice == "Scissors") or \
             (player_choice == "Paper" and computer_choice == "Rock") or \
             (player_choice == "Scissors" and computer_choice == "Paper"):
            player_score += 1
            print("You win!") 
        else:
            computer_score += 1
            print("Computer wins!")

        # Display current scores
        print(f"Player Score: {player_score}")
        print(f"Computer Score: {computer_score}")
        print(f"Ties: {ties}")

def main():    
    """
    Main function that welcomes the user and starts the game
    """
    print("Welcome to Rock, Paper, Scissors Game!")
    Whoiswinner()

if __name__ == "__main__":
    main()
