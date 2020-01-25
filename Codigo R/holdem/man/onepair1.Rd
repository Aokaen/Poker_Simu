\name{onepair1}
\alias{onepair1}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
See if you have a pair.
}
\description{
Sees if you have a pair, and if so, finds the strength of your hand. Used 
by handeval().
}
\usage{
onepair1(x)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{x}{
%%     ~~Describe \code{x} here~~
}
}

\value{
returns 15*15*15*pair + 15*15*next + 15*next + next if you have a pair, or 
0 otherwise.
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
## 15*15*15*pair + 15*15*next + 15*next + next
a1 = unique(x)
a2 = length(a1)
if(a2 == length(x)) return(0)
a3 = rep(0,a2)
for(i in 1:a2) a3[i] = sum(x == a1[i])
a4 = max(a1[a3>1.5])
a5 = sort(c(x[x != a4],rep(0,3)),decreasing=T)
15*15*15*a4 + 225*a5[1] + 15*a5[2] + a5[3]
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
