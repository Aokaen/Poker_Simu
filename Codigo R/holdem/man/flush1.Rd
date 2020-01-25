\name{flush1}
\alias{flush1}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
See if you have a flush
}
\description{
Sees if you have a flush, and if so, how high it is.
}
\usage{
flush1(x, y)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{x}{
vector of numbers of your cards and the board cards, together.
}
  \item{y}{
corresponding suits of your cards and the board cards.
}
}
\details{
Can break down if dealing with 10 cards or more, i.e. if 2 flushes are possible
}
\value{
returns 0 if you don't have a flush,
or 15^4 times top number + 15^3 times 2nd-highest + ... if you do.
%%  ~Describe the value returned
%%  If it is a LIST, use
%%  \item{comp1 }{Description of 'comp1'}
%%  \item{comp2 }{Description of 'comp2'}
%% ...
}

\author{
Frederic Paik Schoenberg
}

\examples{
x = c(2,14,8,8,5,3,4)
y = c(1,2,4,1,1,1,1)
flush1(x,y)
x = c(2,14,8,8,5,3,4)
y = c(1,2,4,1,3,1,1)
flush1(x,y)
##---- Should be DIRECTLY executable !! ----
##-- ==>  Define data, use random,
##--	or do  help(data=index)  for the standard data sets.

## The function is currently defined as
function(x,y){
    ## Can break down if dealing with 10 cards or more, i.e. if 2 flushes are possible
    ## returns 15^4 times top number + 15^3 times 2nd-highest + ...
a1 = mycount1(y)
if(max(a1$ct)<4.5) return(0)
a2 = c(1:length(a1$ct))[a1$ct > 4.5]
a3 = a1$v[a2] ## this is the suit
a4 = sort(x[y == a3],decreasing=T)
sum(15^c(4:0) * a4[1:5])
  } ## end of flush1
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
