\name{straight1}
\alias{straight1}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
See if you have a straight.
}
\description{
Sees if you have a straight, and if so, finds the strength of your hand. Used 
by handeval().
}
\usage{
straight1(x)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{x}{
%%     ~~Describe \code{x} here~~
}
}

\value{
returns the highest card of your straight, or 0 if you don't have one.
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
a1 = sort(unique(x))
if (length(a1)<4.5) return(0)
a3 = 0
n = length(a1)
if(a1[n] == 14) a1 = c(1,a1) ## count ace as both 1 and 14
a2 = length(a1)
for(j in c(5:a2)){ ## j will be the potential highest card of straight
    if( sum(15^c(1:5) * a1[(j-4):j]) == sum(15^c(1:5) * ((a1[j]-4):a1[j]))) a3 = a1[j]
  }
a3
  }	## end of straight1
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
