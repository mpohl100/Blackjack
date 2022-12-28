# Discovering my approach of solving technical problems by implementing a Blackjack solver

## History of this project
In 2021, I just wanted to implement a Blackjack solver as I was interested in how card counters adjust their strategy compared to the standard strategy of blackjack which can be googled easily. I succeeded at that and I have a printed out version of the output of the program. So that is already a nice trophy if you so wish.
Now one year later I realize that it could be valuable to reason about the fundamental traits of my approach on how I tackled this problem. The hope is that finding the core strategies of my technical problem solving can help me in future projects and my day job.

## Developing a roadmap to solve this problem

The following two paragraphs describe the first thoughts I conducted before this repository was created. I decided to record all of my coding and try to implement the solution as fast as possible with thinking breaks in between each recording session.

### What do I already have?

1. I have a Poker project, so business objects like Card, Deck etc can be copied from that project
2. I have a evolutional learning library in C++ which I can use to optimize the percentages of each game situation
3. The evol library has a wrapper around the random number generation facilities of the STL, I can reuse that.
4. I have general expirience with the rule set of Blackjack and I have seen a strategy table in the past.

### What do I have to create?
1. I need to implement the rules of Blackjack and some kind of function which plays the game
2. I need to iterate over all game situations of Blackjack and simulate each situation a couple of thousand times.
3. I will write an evol::Challenge for each game situation and the evol::Chromosome (see the concepts in the evol subdirectory)will be the percentage probability that I will take a certain action.


## Starting to code

I had a clear goal of the classes and functionality I needed to create and I decided to implement it bottom up.
I started by copying the Card and Deck classes and I quickly realized that I need some way to get the current card count of a blackjack hand which I decided to do in the BlackjackPoints header. I also wrote unit tests for this functionality as a bug in that part of the code would be hard to track down.
Also, I needed to implement the dealer card drawing implementing the rule "must draw to 16 and stand at 17" which I also unit tested I hope.
The most difficult part of this project was to implement the playBlackjack function. Creating that interface in the header, I realized that I needed a datastructure to hold all the player decisions of all possible game situations which needed to be designed at the same time. It is always difficult if the scope of what I need to create becomes broad. The BlackjackStrategy header is a good example of me trying to get an elegant solution. As a hand situation and a split situation both have the dealer card in common, I decided to design a BlackjackSituation class as template which has a dealer rank as fixed member and takes the BlackjackPoints for a hand situation and another blackjack rank for the split situation as parameter. I decided to use the spaceship operator to generate the comparison operators for this class in order to use the blackjack situation as key in a std::map as is hsown in the BlackjackStragegy class. This was designed under time pressure and I am quite happy with the result.
After the BlackjackStrategy was designed I started implementing the playBackjackHand function. I realized that in case of a split situation I can use recursion, which was really nice. I also realized that I needed a play mode enum. First I would need to examine all possible situations in normal play mode where you can only draw or stand pat. After discovering the startegy for all possible solutions you would need to play every two card situation as double down to examine those situations. After I solved all situations in normal mode and double down mode I would need to allow splitting hands with the same rank of cards and I could solve all splitting situations as I already know all strategies for doubling down and normal drawing situations.
After implementing that function I decided against unit testing it and voted for generating the solution for a normal deck and comparing it to the results on the internet as the test for the playBlackjackHand function. I decided to throw runtime errors if the action of a game situation was not found in the BlackjackStrategy instance as that would indicate an error in the calling code. 

## The second part of the implementation phase

I think I already finished the Chromosome in the first phase with the percentage class but the BlackjackChallenge still needed to be created. The score function is not complicated as it just plays a game situation 2000 times and returns the summed payoff as its fitness value. 2000 is a realtively low number but it is a result of a nice discovery. In order to evaluate a gae situation accurately I just need to examine the 100% and 0% case, so it is a question of do it or do not do it. Doing something 80% of the time was uninteresting. That realization happened a bit too late. The challenge and chromosome class were already created, so I decided to stick with the implementation and not refactor the code to a bool. In production code for my company I would do the refactoring as the code will be read by other people, but here I still did not get around to doing it as I already have the result I wanted from the code. The valuable lesson is, that deciding too early in the design phase can cause overengineering of the solution.
After implementing the challenge class all I needed was iterating over all blackjack game situations, construct the challenge, call the score function, and print the Blackjack strategy class to std::cout. For the drawing situations I first needed to solve for twenty points, then 19 and so on down to 4 as I could always draw an ace and convert a 19 points situation to a 20 points situation. Furthermore I would need to play optimally in all second situations in order to find the optimal solution for the primary situation. After solving for the drawing situations I needed to solve all double down situations. As those two phases were completed I could then solve the split situations. After implementing that code I did not film myself implementing the counted deck and the pretty printing of the blackjack strategy class as I didn't have any more will power to perform as quickly as possible while recording.

## Resumee

Overall I am very happy to have created this project and to succeed at its implementation. I could reproduce the strategy for the normal deck and I learned how counting the picture cards affects the strategy of the blackjack player. Now I want to reason about my way of solving technical problems. Overall I am very happy with the approach of implementing this project bottom up. It drives the incentive of unit testing the leaf components of your software which is always a good way to prevent bugs from creeping in. I think that being able to formulate the bottom components of your software is an indication, that you understood the technical problem and how much effort you need to make in order to create it.
If I were to implement this top down, I would first need to create the Blackjack strategy class and iterate over all game situations. Then I would implement the playBlackjackHand function and the other needed functionality. I would be incentivized to just press run and step through the code in order to get it correct. By not having the code connected to the main function I HAVE to write unit tests in order to run my code and I HAVE to design the code so that the parts are testable. I didn't realize this prior to this project but I think going bottom up has its advantages over going top down.
Another thing I realized is that I am very disciplined to not repeat myself even under time pressure. I designed the BlackjackSituation class in order to not duplicate the code for the hand situation and the split situation. This is a nice observation for my approach.

