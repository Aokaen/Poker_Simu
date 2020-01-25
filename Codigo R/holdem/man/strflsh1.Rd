\name{strflsh1}
\alias{strflsh1}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
See if you have a straight flush.
}
\description{
Sees if you have a straight flush, and if so, finds the strength of your hand. Used 
by handeval().
}
\usage{
strflsh1(x, y)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{x}{
%%     ~~Describe \code{x} here~~
}
  \item{y}{
%%     ~~Describe \code{y} here~~
}
}

\value{
returns the highest card of your straight flush if you have one, or 0 
otherwise.
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
function(x,y){
a1 = mycount1(y)
if(max(a1$ct)<4.5) return(0)
a2 = c(1:length(a1$ct))[a1$ct > 4.5]
a3 = a1$v[a2] ## this is the suit
a4 = sort(x[y == a3],decreasing=T)
straight1(a4)
  } ## end of strflush1
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
