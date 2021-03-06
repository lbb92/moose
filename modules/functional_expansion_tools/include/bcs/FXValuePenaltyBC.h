//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef FXVALUEPENALTYBC_H
#define FXVALUEPENALTYBC_H

#include "FunctionPenaltyDirichletBC.h"

class FXValuePenaltyBC;

template <>
InputParameters validParams<FXValuePenaltyBC>();

/**
 * Defines an FX-based BC that strongly encourages the values to match
 */
class FXValuePenaltyBC : public FunctionPenaltyDirichletBC
{
public:
  FXValuePenaltyBC(const InputParameters & parameters);
};

#endif // FXVALUEPENALTYBC_H
