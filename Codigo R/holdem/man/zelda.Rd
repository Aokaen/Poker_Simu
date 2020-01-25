\name{zelda}
\alias{zelda}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
A sample function that does not necessarily go all in or fold.
}
\description{
This function bets, raises, calls, or folds depending mainly on the strength of 
its hand and the number of players left.
}
\usage{
zelda(numattable1, crds1, board1, round1, currentbet, mychips1, 
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
pre-flop:
	 AK: Make a big raise if nobody has yet. Otherwise call.
	 AQ: call a small raise, or make one if nobody has yet.
	 AJ, AT, KQ, KJ, QJ: call a tiny raise.
	 A9, KT, K9, QT, JT, T9: call a tiny raise if in late position (within 2 of the dealer).
	 Suited A2-AJ: call a small raise.
	 22-99: call a small raise.
	 TT-KK: make a huge raise. If someone's raised huge already, then go all in.
	 AA: make a small raise. If there's been a raise already, 
	 then double how much it is to you.
post-flop: 
	 If there's a pair on the board and you don't have a set, then check/call up to small bet.
	 Same thing if there's 3-of-a-kind on the board and you don't have a full house or more.
	 If you have top pair or an overpair or two pairs or a set, make a big bet 
	 (call any bigger bet). 
	 Otherwise, if nobody's made even a small bet yet, 
	 then with prob. 20\% make a big bluff bet.
	 If you're the last to decide and nobody's bet yet, then increase this prob. to 50\%.
	 If you have an inside straight draw or flush draw then make a small bet 
	 (call any bigger bet).
	 If you have a straight or better, then just call.
	 Otherwise fold.
after turn: 
	 If there's a pair on the board and you don't have a set, then check/call up to small bet.
	 Same thing if there's 3-of-a-kind on the board and you don't have a full house or more.
	 Otherwise, if you have top pair or better, go all in.
	 If you had top pair or overpair but now don't, then check/call a medium bet but fold to more.
	 If you have an inside straight draw or flush draw then check/call a medium bet as well.
	 Otherwise check/fold.
after river: 
	 If there's a pair on the board and you don't have a set, then check/call up to small bet.
	 Same thing if there's 3-of-a-kind on the board and you don't have a full house or more.
	 Otherwise, if you have two pairs or better, go all in.
	 If you have one pair, then check/call a small bet.
	 With nothing, go all-in with probability 10\%; otherwise check/fold.

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
function(numattable1, crds1, board1,  round1, currentbet,  mychips1, pot1, 
    roundbets, blinds1, chips1, ind1, dealer1, tablesleft){
    a1 = 0 ## how much I'm gonna end up betting. Note that the default is zero.
    a2 = min(mychips1, currentbet) ## how much it costs to call
    
    if(round1 == 1){ ## pre-flop:
	## AK: Make a big raise if nobody has yet. Otherwise call.
	## AQ: call a small raise, or make one if nobody has yet.
	## AJ, AT, KQ, KJ, QJ: call a tiny raise.
	## A9, KT, K9, QT, JT, T9: call a tiny raise if in late position 
	## (within 2 of the dealer).
	## Suited A2-AJ: call a small raise.
	## 22-99: call a small raise.
	## TT-KK: make a huge raise. If someone's raised huge already, then go all in.
	## AA: make a small raise. If there's been a raise already, 
	## then double how much it is to you.
	
	a3 = 2*blinds1+1 ## how much a tiny raise would be
	a4 = 4*blinds1+1 ## how much a small raise would be
	a5 = max(8*blinds1,mychips1/4)+1 ## how much a big raise would be
	a6 = max(12*blinds1,mychips1/2)+1 ## how much a huge raise would be
	a7 = dealer1 - ind1
	if(a7 < -.5) a7 = a7 + numattable1 ## your position: a7 = how many hands til you're dealer
	
	if((crds1[1,1] == 14) && (crds1[2,1] == 13)){
	    a1 = max(a2,a5)
	}
	if((crds1[1,1] == 14) && (crds1[2,1] == 12)){
	    if(a2 < a4){
		a1 = a4
	    } else if(a2 > a5){
		a1 = 0
	    } else a1 = a2
	}
	if(((crds1[1,1] == 14) && ((crds1[2,1] < 11.5) && (crds1[2,1] > 9.5))) || 
	    ((crds1[1,1] == 13) && (crds1[2,1] > 10.5)) ||
	    ((crds1[1,1] == 12) && (crds1[2,1] == 11))){
	    if(a2 < a3) a1 = a2
	}
	if(((crds1[1,1] == 14) && (crds1[2,1] == 9)) || 
	    ((crds1[1,1] == 13) && ((crds1[2,1] == 10) || (crds1[2,1] == 9))) ||
	    ((crds1[1,1] == 12) && (crds1[2,1] == 10)) ||
	    ((crds1[1,1] == 11) && (crds1[2,1] == 10)) ||
	    ((crds1[1,1] == 10) && (crds1[2,2] == 9))){
	    if((a2 < a3) && (a7<2.5)) a1 = a2
	}
	if((crds1[1,2] == crds1[2,2]) && (crds1[1,1] == 14) && (crds1[2,1] < 11.5)){
	    if(a2<a4) a1 = a2
	    ## Note: this trumps the previous section, since it comes later in the code.
	}
	if((crds1[1,1] == crds1[2,1])){ ## pairs:
	    if(crds1[1,1] < 9.5){
		if(a2 < a4) a1 = a2
	    } else if(crds1[1,1] < 13.5){
		if(a2<a5) a1 = a5 else a1 = mychips1
	    } else {
		if(a2 < blinds1 + .5) a1 = a4 else a1 = min(2*a2,mychips1)
	    }
	}
    }
    if(round1 == 2){ ## post-flop: 
	## If there's a pair on the board and you don't have a set, then check/call up to small bet.
	## Same thing if there's 3-of-a-kind on the board and you don't have a full house or more.
	## If you have top pair or an overpair or two pairs or a set, 
	## make a big bet (call any bigger bet). 
	## Otherwise, if nobody's made even a small bet yet, 
	## then with prob. 20\% make a big bluff bet.
	## If you're the last to decide and nobody's bet yet, then increase this prob. to 50\%.
	## If you have an inside straight draw or flush draw then make 
	## a small bet (call any bigger bet).
	## If you have a straight or better, then just call.
	## Otherwise fold.
	
	a5 = min(sum(roundbets[,1]),mychips1) ## how much 
	## a big bet would be (prev round's pot size)
	a6 = min(.5*sum(roundbets[,1]),mychips1) ## how much a small bet would be	
	x = handeval(c(crds1[1:2,1], board1[1:3,1]), 
	c(crds1[1:2,2], board1[1:3,2])) ## what you have
	x1 = handeval(c(board1[1:3,1]),c(board1[1:3,2])) ## what's on the board
	y = straightdraw1(c(crds1[1:2,1], board1[1:3,1]))
	z = flushdraw1(c(crds1[1:2,2], board1[1:3,2]))
	topcard1 = max(board1[1:3,1])
	a7 = runif(1) ## random number uniformly distributed between 0 and 1
	a8 = (1:numattable1)[roundbets[,1] == roundbets[ind1,1]] ## others who can still bet
	## The next 5 lines may seem weird, but the purpose is explained in the next comment:
	a9 = a8 - dealer1
	for(i in 1:length(a9)) if(a9[i]<.5) a9[i] = a9[i] + numattable1
	a10 = ind1 - dealer1
	if(a10 < .5) a10 = a10 + numattable1
	a11 = 2*(a10 == max(a9))   ## So a11 = 2 if you're last to decide; otherwise a11 = 0.
	
	if((x1 > 1000000) && (x < 3000000)){
	    if(a2 < a6) a1 = a2
	} else if((x1 > 3000000) && (x < 6000000)){
	    if(a2 < a6) a1 = a2
	} else if(x > 1000000 + 15^3*topcard1){
	    a1 = max(a5,a2)
	} else if((a2 < a6) && ((a7 < .20) || ((a7 < .50) && (a11>1)))){
	    a1 = a6
	}
	if((y == 4) || (z == 4)) a1 = max(a6, a2)
	if(x > 4000000) a1 = a2
    }
    if(round1 == 3){ ## after turn: 
	## If there's a pair on the board and you don't have a set, then check/call up to small bet.
	## Same thing if there's 3-of-a-kind on the board and you don't have a full house or more.
	## Otherwise, if you have top pair or better, go all in.
	## If you had top pair or overpair but now don't, then check/call a medium bet 
	## but fold to more.
	## If you have an inside straight draw or flush draw then check/call a medium bet as well.
	## Otherwise check/fold.
	a6 = min(1/3*sum(roundbets[,1:2]),mychips1) ## small bet (1/3 of prev round's pot size)
	a5 = min(.75*sum(roundbets[,1:2]),mychips1) ## medium bet (3/4 of prev round's pot size)
	x = handeval(c(crds1[1:2,1], board1[1:4,1]), 
	c(crds1[1:2,2], board1[1:4,2])) ## what you have
	x1 = handeval(c(board1[1:4,1]),c(board1[1:4,2])) ## what's on the board
	y = straightdraw1(c(crds1[1:2,1], board1[1:4,1]))
	z = flushdraw1(c(crds1[1:2,2], board1[1:4,2]))
	topcard1 = max(board1[1:4,1])
	oldtopcard1 = max(board1[1:3,1])
	if((x1 > 1000000) && (x < 3000000)){
	    if(a2 < a6) a1 = a2
	} else if((x1 > 3000000) && (x < 6000000)){
	    if(a2 < a6) a1 = a2
	} else if(x > 1000000 + 15^3*topcard1){
	    a1 = mychips1
	} else if(x > 1000000 + 15^3*oldtopcard1){
	    if(a2 < a5) a1 = a2
	} else if((y == 4) || (z == 4)){
	    if(a2 < a5) a1 = a2
	}
    }
    if(round1 == 4){ ## after river: 
	## If there's a pair on the board and you don't have a set, then check/call up to small bet.
	## Same thing if there's 3-of-a-kind on the board and you don't have a full house or more.
	## Otherwise, if you have two pairs or better, go all in.
	## If you have one pair, then check/call a small bet.
	## With nothing, go all-in with probability 10\%; otherwise check/fold.
	a6 = .45+runif(1)/10  ## random number between .45 and .55
	a5 = min(a6*sum(roundbets[,1:3]),mychips1) ## small bet: 
	## around 1/2 of pot size; VARIES RANDOMLY
	x = handeval(c(crds1[1:2,1], board1[1:5,1]), c(crds1[1:2,2], board1[1:5,2]))
	x1 = handeval(c(board1[1:5,1]),c(board1[1:5,2])) ## what's on the board
	if((x1 > 1000000) && (x < 3000000)){
	    if(a2 < a5) a1 = a2
	} else if((x1 > 3000000) && (x < 6000000)){
	    if(a2 < a5) a1 = a2
	} else if(x > 2000000){
	    a1 = mychips1
	} else if(x > 1000000){
	    if(a2 < a5) a1 = a2
	} else if(runif(1)<.10){
	    a1 = mychips1
	}
    }
    round(a1)
  } ## end of zelda
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
