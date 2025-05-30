#include "fplll-interface.hpp"
#include "mutablemat.hpp"

#ifdef HAVE_FPLLL
#include <stddef.h>
#include <fplll.h>
#endif

bool fp_LLL(MutableMatrix *M, MutableMatrix *U, int strategy)
{
#ifndef HAVE_FPLLL
  ERROR("fplll is not available (configure M2 with fplll!)");
  return 0;
#else
  assert(U == NULL);
  double delta = 0.99;
  double eta = 0.51;
  fplll::LLLMethod method = fplll::LM_WRAPPER;
  fplll::FloatType floatType = fplll::FT_DEFAULT;
  int precision = 0;
  int flags = fplll::LLL_DEFAULT;

  int ncols = static_cast<int>(M->n_rows());
  int nrows = static_cast<int>(M->n_cols());

  fplll::ZZ_mat<mpz_t> mat(nrows, ncols);

  for (int i = 0; i < nrows; i++)
    for (int j = 0; j < ncols; j++)
      {
        ring_elem a;
        if (M->get_entry(j, i, a))
          {
            mpz_set(mat[i][j].get_data(), a.get_mpz());
          }
      }

  int result =
      lll_reduction(mat, delta, eta, method, floatType, precision, flags);

  switch (result)
    {
      case fplll::RED_SUCCESS:
        break;
      case fplll::RED_BABAI_FAILURE:
        ERROR("Error in fpLLL");
        return 0;
      case fplll::RED_LLL_FAILURE:
        ERROR("infinite loop in LLL");
        return 0;
      default:
        ERROR("unknown error in fpLLL");
        return 0;
    }

  /* Put this back into M */
  mpz_t a;
  mpz_init(a);

  for (int j = 0; j < ncols; j++)
    for (int i = 0; i < nrows; i++)
      {
        mpz_set(a, mat[i][j].get_data());
        ring_elem b = globalZZ->from_int(a);
        M->set_entry(j, i, b);
      }
  mpz_clear(a);
  return true;
#endif
}

// Local Variables:
// compile-command: "make -C $M2BUILDDIR/Macaulay2/e  "
// indent-tabs-mode: nil
// End:
