\name{xena}
\alias{xena}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
A sample function that goes all in or folds
}
\description{
Goes all in with a pair of 10s or higher, 
or with a pair of 7s or higher if there are 6 or fewer players,
or with any cards if you have less than 2 big blinds.
With AK or AQ, all in with probability 75\%.
Or if nobody's raised yet, under certain conditions (see details).
}
\usage{
xena(numattable1, crds1, board1, round1, currentbet, mychips1, 
pot1, roundbets, blinds1, chips1, ind1, dealer1, tablesleft)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{numattable1}{
(integer) number of players at the table
}
  \item{crds1}{
(2x2 matrix) your hole cards.
cards1[1,1] = the number of card 1 (between 2 and 14). 
cards[1,2] = suit of card 1 (between 1 and 4).
cards1[2,1] = the number (2-14) of card 2. 
cards[2,2] = suit of card 2 (1-4).
}
  \item{board1}{
(5x2 matrix) the board cards.
board1[1,1] = number of first card (2-14).
board1[1,2] = suit (1-4) of first card. 
Both are zero if the card hasn't been seen yet. 
For instance, if bettinground1 < 3, then board[4,1] = board1[4,2] = 0.
}
  \item{round1}{
(integer) which betting round it is.
1 = preflop, 2 = after flop, 3 = after turn, 4 = after river.
}
  \item{currentbet}{
(integer) how much more it is to you to stay in, right now.
}
  \item{mychips1}{
(integer) how many chips you have left at the moment.
}
  \item{pot1}{
(integer) how much is in the pot at the moment.
}
  \item{roundbets}{
(numattable1 x 4 matrix) matrix of all past bets during this hand.
roundbets[i,j] = total amount the player in seat i put in, in betting round j.
}
  \item{blinds1}{
(integer) big blind amount.
}
  \item{chips1}{
(vector of length numattable1) list of how many chips everyone has.
chips1[i] = how many chips the player in seat i has left.
}
  \item{ind1}{
(integer) which seat you're in.  
(So, mychips1 = chips1[ind1]).
}
  \item{dealer1}{
(integer) which seat the dealer is in. 
}
  \item{tablesleft}{
(integer) how many tables are left in the tournament (including yours). 
}
}
\details{
Goes all in with a pair of 10s or higher, 
or with a pair of 7s or higher if there are 6 or fewer players,
or with any cards if you have less than 2 big blinds.
With AK or AQ, all in with probability 75\%.
If nobody's raised yet,
     ... and if there are 3 or fewer players left behind you,
         then go all in with any pair or any ace.
     ... and there's only 1 or 2 players behind you,
         then go all in with any cards.    

When this function is called from tourn1(),
cards1[2,1] is always less than or equal to cards1[1,1].
If the player in the big blind seat does not have enough chips to pay the 
big blind, then blinds1 is still the amount that the big blind would have 
been.
If only 2 players are left, then tourn1() uses the convention that the "dealer" 
is the big blind in determining dealer1.
}
\value{
integer indicating the number of chips you are betting. 0 means fold.
}
\references{
Schoenberg, F. (2011). An Introduction to Probability with Texas Holdem 
Examples. Taylor and Francis, New York.
}
%% ~Make other sections like Warning with \section{Warning }{....} ~

\examples{
##---- Should be DIRECTLY executable !! ----
##-- ==>  Define data, use random,
##--	or do  help(data=index)  for the standard data sets.

## The function is currently defined as
function(numattable1, crds1, board1,  round1, currentbet, mychips1, pot1,
    roundbets, blinds1, chips1, ind1, dealer1, tablesleft){
    ## if pair of 10s or higher, all in for sure, no matter what.
    ## if AK or AQ, all in with probability 75\%.
    ## if pair of 7s or higher and there are 6 or fewer players 
    ##      at your table (including you), then all in. 
    ## if your chip count is less than twice the big blind, go all in with any cards.
    ## if nobody's raised yet:
    ##     ... and if there are 3 or fewer players left behind you,
    ##              then go all in with any pair or any ace.
    ##     ... and there's only 1 or 2 players behind you,
    ##              then go all in with any cards.    
    a1 = 0
    x = runif(1)               ## x is a random number between 0 and 1.
    y = max(roundbets[,1])     ## y is the maximum bet so far.
    big1 = dealer1 + 2
    if(big1 > numattable1) big1 = big1 - numattable1
    z = big1 - ind1
    if(z<0) z = z + numattable1 
    ## the previous 4 lines make it so z is the number of players left to act behind you.
    if((crds1[1,1] == crds1[2,1]) && (crds1[2,1] > 9.5)) a1 = mychips1
    if((crds1[1,1] == 14) && (crds1[1,2]>11.5) && (x<.75)) a1 = mychips1
    if((crds1[1,1] == crds1[2,1]) && (crds1[2,1] > 6.5) && (numattable1 < 6.5)) a1 = mychips1
    if(mychips1 < 2*blinds1) a1 = mychips1
    if(y <= blinds1){
	if((z < 3.5) && ((crds1[1,1] == crds1[2,1]) || (crds1[1,1] == 14))) a1 = mychips1
	if(z < 2.5) a1 = mychips1
    }
    a1
  } ## end of xena
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
