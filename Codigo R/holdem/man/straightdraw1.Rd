\name{straightdraw1}
\alias{straightdraw1}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
See if you have a straight draw.
}
\description{
Sees how many possibilities there are that will make a straight for you.
}
\usage{
straightdraw1(x)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{x}{
%%     ~~Describe \code{x} here~~
}
}

\value{
returns 26 if you already have a straight.
returns 4 is there are 2 possibilities for a straight. 
returns 2 for a gutshot straight draw.
returns 0 otherwise.
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
straightdraw1(c(2,5,6,7,9,14))
straightdraw1(c(4,5,6,7,9,14))
##---- Should be DIRECTLY executable !! ----
##-- ==>  Define data, use random,
##--	or do  help(data=index)  for the standard data sets.

## The function is currently defined as
function(x){
    ## returns 4 is there are 2 possibilities for a straight. 
    ## returns 2 for a gutshot straight draw.
    ## returns 0 otherwise
    ## Note: returns 26 if you already have a straight!
    a1 = 0
    for(i in c(2:14)){
	a2 = straight1(c(i,x))
	if(a2 > .5) a1 = a1 + 1
    }
    a1 * 2 
  }	## end of straightdraw1
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
