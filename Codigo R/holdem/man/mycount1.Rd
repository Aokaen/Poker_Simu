\name{mycount1}
\alias{mycount1}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
counts the unique values in a vector
}
\description{
returns sorted unique values of x and how many times each appears
}
\usage{
mycount1(x)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{x}{
%%     ~~Describe \code{x} here~~
}
}

\value{
 and their cardinality
%%  ~Describe the value returned
%%  If it is a LIST, use
  \item{v }{sorted unique values in x}
  \item{ct }{cardinality of each of the values}
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
    ## returns sorted unique values of x and how many times each appears
b1 = sort(unique(x),decreasing=T)
b2 = length(b1)
b3 = rep(0,b2)
for(i in 1:b2) b3[i] = sum(x == b1[i])
list(v=b1, ct = b3)
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
