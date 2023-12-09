This problem was just ripe for the opportunity to use classes. I started with the Hand class, and quickly realised I need a Card class as well to easily be able to get a card's value and compare cards, similar to what I needed to do with hands. I added methods to check different types of hands in the puzzle's version of poker and to simplify things even further, made a hand type enum to easily check which hands are bigger than which.

Once I had things set up, the actual code to solve the puzzle was minimal. All I had to do is sort the list of hands according to my comparison functions (I overloaded the > and the == operators), and calculate the winnings

Part two made things more interesting, but all the time I spent setting things up with classes paid off. All I had to do was change the logic in each of the hand type check functions to include the possibilities of jokers, and the rest worked on its own. Realising that when there's a tie, the Joker remains a J simplified things a lot
