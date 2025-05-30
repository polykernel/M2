--- status: done
--- author(s): dan
--- notes: 

document { 
     Key => homology,
     Headline => "general homology functor",
     "Most applications of this functor are dispatched through ", TT "HH", ".
     If it is intended that ", TT "i", " be of class ", TO "ZZ", ", 
     ", TT "M", " be of class ", TT "A", ", and ", TT "N", " be of
     class ", TT "B", ", then the method for computing ", TT "HH_i(M,N)", " can be installed with 
     code of the following form.",
     PRE "     homology(ZZ, A, B) := opts -> (i,M,N) -> ...",
     SeeAlso => {"cohomology", "HH", "ScriptedFunctor"}
     }

document { 
     Key => (homology,Matrix,Matrix),
     Headline => "homology of a pair of maps",
     Usage => "M = homology(f,g)",
     Inputs => { "f", "g" },
     Outputs => {
	  "M" => {"computes the homology module ", TT "(kernel f)/(image g)", "."}
	  },
     "Here ", TT "g", " and ", TT "f", " should be composable maps with ", TT "f*g", "
     equal to zero.",
     PARA {
	  "In the following example, we ensure that the source of ", TT "f", " and the target of
	  ", TT "f", " are exactly the same, taking even the degrees into account, and we ensure
	  that ", TT "f", " is homogeneous."},
     EXAMPLE {
	  "R = QQ[x]/x^5;",
	  "f = map(R^1,R^1,{{x^3}}, Degree => 3)",
	  "M = homology(f,f)",
	  "prune M"
	  }
     }

