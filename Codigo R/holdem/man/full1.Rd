\name{full1}
\alias{full1}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
See if you have a full house.
}
\description{
Sees if you have a full house.
}
\usage{
full1(x)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{x}{
Numbers of your cards and the board cards.
}
}

\value{
15 times the number of your triplet + the number of your pair in your best 
five card hand, or 0 if you don't have a full house. 
For instance, if you have 22 and the board is 2AAQQ, then it returns
15*2 + 14 = 44.
%%  ~Describe the value returned
%%  If it is a LIST, use
%%  \item{comp1 }{Description of 'comp1'}
%%  \item{comp2 }{Description of 'comp2'}
%% ...
}

%% ~Make other sections like Warning with \section{Warning }{....} ~

\examples{
x = c(2,2,2,14,14,12,12)
full1(x)
##---- Should be DIRECTLY executable !! ----
##-- ==>  Define data, use random,
##--	or do  help(data=index)  for the standard data sets.

## The function is currently defined as
function(x){
a1 = mycount1(x)
a2 = sort(a1$ct,decreasing=T)
if(length(a2) < 1.5) return(0)
if(a2[1] < 2.5) return(0)
if(a2[2] < 1.5) return(0)
a3 = min(c(1:length(a1$ct))[a1$ct > 2.5])
a4 = a1$v[a3] ## the number of the trip
a5 = a1$ct[-a3]
a6 = a1$v[-a3]
a7 = min(c(1:length(a5))[a5 > 1.5]) ## the number of the pair
a8 = a6[a7]
15*a4 + a8
  }  ## end of full1
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
