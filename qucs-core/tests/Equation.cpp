/*
 * Equation.cpp - Unit tests for equation solver
 *
 * Copyright (C) 2018 Andrew Dona-Couch <qucs-dev@andrewcou.ch>
 *
 * TODO: insert header here
 *
 */

#include "qucs_typedefs.h"
#include "equation.h"

#include "testDefine.h"   // constants used in tests
#include "gtest/gtest.h"  // Google Test

#define C(c) ((qucs::eqn::constant *) (c))
#define R(r) ((qucs::eqn::reference *) (r))

TEST (constant, evalType) {
  qucs::eqn::node * dbl = new qucs::eqn::constant (qucs::eqn::TAG_DOUBLE);
  ASSERT_EQ (qucs::eqn::TAG_DOUBLE, dbl->evalType ());
  delete dbl;

  qucs::eqn::node * cmp = new qucs::eqn::constant (qucs::eqn::TAG_COMPLEX);
  ASSERT_EQ (qucs::eqn::TAG_COMPLEX, cmp->evalType ());
  delete cmp;
}

TEST (constant, evaluate) {
  qucs::eqn::node * dbl = new qucs::eqn::constant (qucs::eqn::TAG_DOUBLE);
  ASSERT_EQ (dbl, dbl->evaluate ());
  delete dbl;

  qucs::eqn::node * cmp = new qucs::eqn::constant (qucs::eqn::TAG_COMPLEX);
  ASSERT_EQ (cmp, cmp->evaluate ());
  delete cmp;
}

TEST (constant, differentiate) {
  char name[] = "";

  qucs::eqn::node * dbl = new qucs::eqn::constant (qucs::eqn::TAG_DOUBLE);
  qucs::eqn::node * dblD = dbl->differentiate (name);
  ASSERT_EQ (0, dblD->evaluate ()->getResultDouble ());
  delete dblD;
  delete dbl;

  qucs::eqn::node * cmp = new qucs::eqn::constant (qucs::eqn::TAG_COMPLEX);
  qucs::eqn::node * cmpD = cmp->differentiate (name);
  ASSERT_EQ (0, cmpD->evaluate ()->getResultDouble ());
  delete cmpD;
  delete cmp;
}

TEST (constant, toString) {
  qucs::eqn::node * dbl = new qucs::eqn::constant (qucs::eqn::TAG_DOUBLE);
  C(dbl)->d = 42.0;
  ASSERT_STREQ ("42", dbl->toString ());
  delete dbl;

  qucs::eqn::node * cmp = new qucs::eqn::constant (qucs::eqn::TAG_COMPLEX);
  C(cmp)->c = new nr_complex_t (42.0, -1.0);
  ASSERT_STREQ ("(42-j1)", cmp->toString ());
  delete cmp;

  qucs::eqn::node * cmp2 = new qucs::eqn::constant (qucs::eqn::TAG_COMPLEX);
  C(cmp2)->c = new nr_complex_t (42.0, 0.0);
  ASSERT_STREQ ("42", cmp2->toString ());
  delete cmp2;
}

TEST (reference, replace) {
  char foo[] = "foo";
  char bar[] = "bar";
  char baz[] = "baz";

  qucs::eqn::node * ref = new qucs::eqn::reference ();
  R(ref)->n = strdup (foo);
  ref->replace (foo, bar);
  ASSERT_STREQ (bar, R(ref)->n);
  delete ref;

  qucs::eqn::node * ref2 = new qucs::eqn::reference ();
  R(ref2)->n = strdup (foo);
  ref2->replace (bar, baz);
  ASSERT_STREQ (foo, R(ref2)->n);
  delete ref2;
}

TEST (reference, toString) {
  char foobar[] = "foobar";

  qucs::eqn::node * ref = new qucs::eqn::reference ();
  R(ref)->n = strdup (foobar);
  ASSERT_STREQ (foobar, ref->toString());
  delete ref;
}

TEST (reference, evalType) {
  char foobar[] = "foobar";

  qucs::eqn::node * ref = new qucs::eqn::reference ();
  R(ref)->n = strdup (foobar);
  ASSERT_EQ (qucs::eqn::TAG_UNKNOWN, ref->evalType());
  delete ref;
}

TEST (reference, differentiate) {
  char foo[] = "foo";
  char bar[] = "bar";

  qucs::eqn::node * ref = new qucs::eqn::reference ();
  R(ref)->n = strdup (foo);
  qucs::eqn::node * refD = ref->differentiate (foo);
  ASSERT_EQ (1, refD->evaluate ()->getResultDouble ());
  delete ref;

  qucs::eqn::node * ref2 = new qucs::eqn::reference ();
  R(ref2)->n = strdup (foo);
  qucs::eqn::node * ref2D = ref2->differentiate (bar);
  ASSERT_EQ (0, ref2D->evaluate ()->getResultDouble ());
  delete ref2;
}
