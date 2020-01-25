\name{flushdraw1}
\alias{flushdraw1}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
Sees if you have a flush draw.
}
\description{
Calculates how many you have of the suit of which you have most.
}
\usage{
flushdraw1(x)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{x}{
Suits of your cards and the board cards (together, as a vector).
}
}

\value{
returns the number you have of a suit, i.e. 4 if you have a flush draw, or 
5 (or more) if you have a flush already.
}

\author{
Frederic Paik Schoenberg
}

%% ~Make other sections like Warning with \section{Warning }{....} ~

\examples{
x = c(1,2,4,1,3,1,1)
flushdraw1(x)
##---- Should be DIRECTLY executable !! ----
##-- ==>  Define data, use random,
##--	or do  help(data=index)  for the standard data sets.

## The function is currently defined as
function(x){
    a1 = mycount1(x)
    max(a1$ct)
  } ## end of flushdraw1
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
