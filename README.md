# Blackjack Simulator
The aim of this project is to simulate hundreds of hands of blackjack to analyse how different strategies and card counting may affect the expected value of the game. Hopefully, the results will discourage any potential gambling and enlighten us to how advantaged players actually make money against the odds.

NOTE: If you have a gambling addiction, don't be afraid to reach out for help. Visit https://www.gambleaware.nsw.gov.au/ for support or call 1800 858 858.

## Basic Strategy
Basic strategy is taught basically everywhere and is fundamentally how blackjack is "supposed" to be played. It focuses on optimal play, albeit without any additional advantage from card counting.

![alt text](https://www.blackjackapprenticeship.com/wp-content/uploads/2018/08/BJA_Basic_Strategy.jpg)

Source: https://www.blackjackapprenticeship.com/wp-content/uploads/2018/08/BJA_Basic_Strategy.jpg

Notice that even by playing blackjack perfectly according to the chart above (given the house rules allow for all these scenarios), there is still a house advantage of 0.5%. Meaning, for every dollar you bet, you are expected to lose 0.5% of that everytime.

## Card Counting
So what is card counting? The concept is simple enough. A common method is to +1 to your count whenever you see a 2-6, add 0 for 7-9 and -1 for 10 and up.

![alt text](https://www.lasvegasadvisor.com/gambling-with-an-edge/wp-content/uploads/2017/08/cards.jpg)

Source: https://www.lasvegasadvisor.com/gambling-with-an-edge/wp-content/uploads/2017/08/cards.jpg

That number in your head is the "running count". What we're really interested in is the "true count".

**True Count = Running Count/Decks Remaining**

In this simulator, we're assuming that we're playing 6-deck blackjack, so the dealer would have 6 decks in total shuffled together. To get the true count, we simply divide the running count by the decks remaining. So for a running count of +5, with 5 decks remaining, that would be a true count of +5/5 = +1.

And for every +1 true count, we would increase our betting size by 1 unit. Whatever that unit may be. It could be $10, $20 whatever value we want to bet with. In this simulator, the default value for the minimum bet is $10 and that will also be our betting unit. We will keep betting the minimum, until our true count tells us it's a good time to raise our bet.

## How Realistic Is This?
Most casinos are aware of these by now and would shuffle their decks pretty soon, you would be lucky to find a spot where they would wait for 50% of the shoe to have been played before shuffling. In major casinos you would probably see CSMs (Continuous Shuffling Machines), where cards played would instantly be reshuffled into the pool. This makes it extremely hard or even impossible to count cards. Whether or not it is possible to beat CSMs is a topic for another time.

## TODO
- Remove code repetition between Dealer class and Player class.
- Enable Double and Split actions
- Enable multiple round blackjack
- Enable payouts
- Add card counting and changing bet sizes appropriately
- Add manual play mode
