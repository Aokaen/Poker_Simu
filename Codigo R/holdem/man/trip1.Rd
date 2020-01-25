\name{trip1}
\alias{trip1}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
See if you have 3 of a kind.
}
\description{
Sees if you have 3 of a kind, and if so, finds the strength of your hand. Used 
by handeval().
}
\usage{
trip1(x)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{x}{
%%     ~~Describe \code{x} here~~
}
}

\value{
Returns 225 * your triple + 15 * your next highest card + your next 
highest card if you have 3 of a kind, or 0 otherwise.
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
##---- Should be DIRECTLY executable !! ----
##-- ==>  Define data, use random,
##--	or do  help(data=index)  for the standard data sets.

## The function is currently defined as
function(x){
## 225*triple + 15*next + next
a1 = mycount1(x)
a2 = a1$v
a3 = a1$ct
a4 = sum(a3 > 2.5)
if(a4 < 0.5) return(0)
a5 = sort(a2[a3>2.5],decreasing=T)
a6 = sort(c(0,0,x[(x != a5[1])]),decreasing=T)
225*a5[1] + 15*a6[1] + a6[2]
  }    ## end of trip1
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
