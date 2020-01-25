\name{four1}
\alias{four1}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
Sees if you have 4 of a kind
}
\description{
Sees if you have 4 of a kind.
}
\usage{
four1(x)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{x}{
Numbers of your cards and the board cards.
}
}

\value{
15*number of the foursome + the number of your next highest other card.
For instance, if your best 5 card hand is 8888K, then it will return 15*8 
+ 13 = 133.
Returns 0 if you don't have 4 of a kind.
%%  ~Describe the value returned
%%  If it is a LIST, use
%%  \item{comp1 }{Description of 'comp1'}
%%  \item{comp2 }{Description of 'comp2'}
%% ...
}

\author{
Frederic Paik Schoenberg
}

%% ~Make other sections like Warning with \section{Warning }{....} ~

\examples{
x = c(8,8,8,8,13,12,2)
four1(x)
x = c(8,8,8,3,13,12,2)
four1(x)
##---- Should be DIRECTLY executable !! ----
##-- ==>  Define data, use random,
##--	or do  help(data=index)  for the standard data sets.

## The function is currently defined as
function(x){
## 15*number of the foursome + next
a1 = mycount1(x)
a2 = a1$v
a3 = a1$ct
a4 = sum(a3 > 3.5)
if(a4 < 0.5) return(0)
a5 = sort(a2[a3>3.5],decreasing=T)
a6 = sort(c(0,x[(x != a5[1])]),decreasing=T)
15*a5[1] + a6[1]
  }    ## end of four1
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
