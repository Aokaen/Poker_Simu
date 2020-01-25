\name{twopair1}
\alias{twopair1}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
See if you have two pairs.
}
\description{
Sees if you have two pairs, and if so, finds the strength of your hand. Used 
by handeval().
}
\usage{
twopair1(x)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{x}{
%%     ~~Describe \code{x} here~~
}
}

\value{
225 * your higher pair + 15 * the lower pair + the number of your kicker, 
if you have two pairs, or 0 otherwise.
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
## 225*highpair + 15*lowpair + next
a1 = mycount1(x)
a2 = a1$v
a3 = a1$ct
a4 = sum(a3>1.5)
if(a4<1.5) return(0)
a5 = sort(a2[a3>1.5],decreasing=T)
a6 = max(c(0,a2[(a2 != a5[1]) & (a2 != a5[2])]))
225*a5[1] + 15*a5[2] + a6
  }    ## end of twopair1
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
