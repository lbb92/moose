//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef POROUSFLOWDICTATOR_H
#define POROUSFLOWDICTATOR_H

#include "GeneralUserObject.h"
#include "Coupleable.h"

class PorousFlowDictator;

template <>
InputParameters validParams<PorousFlowDictator>();

/**
 * This holds maps between the nonlinear variables
 * used in a PorousFlow simulation and the
 * variable number used internally by MOOSE, as
 * well as the number of fluid phases and
 * the number of fluid components.
 *
 * The Dictator performs sanity checks on all
 * PorousFlow simulations and helps users
 * rectify errors (for instance if parts of
 * the input file suggest it is a 2-phase
 * simulation, while other parts suggest it
 * is 1-phase).
 *
 * All PorousFlow Materials and Kernels calculate
 * and use derivatives with respect to all the variables
 * mentioned in this Object, at least in principal
 * (in practice they may be lazy and not compute
 * all derivatives).
 */

/**
                                  `  `:;@;:.:::#@@@'.`
                           `    ,@;@@@@@@@@@@@@@@@@@@@@'';''``
                     ,;@@@@@@@@@@@@T@@@@@H@@@@@E@@@@@@@@++@@@+:.:.`
            '@@'@@@@@@@D@@@@@I@@@@@C@@@@@T@@@@@A@@@@@T@@@@@O@@@@@R@@@@@@..`
     `..,;@@@@@@@@@@@@@@@@@@@@@@@@@@@@I@@@@@S@@@@@@@@@@@@@@@@@@@@@@@@@@@;.
 .:@@@@@@@@@@@@@@@@@@@@W@@@@@A@@@@@T@@@@@C@@@@@H@@@@@I@@@@@N@@@@@G@@@@@@@@@#;:.`
 .:@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:,@@@@@@@@@@+` ``
 ,@@@@@@@@@@@';'@@@@@@@@@@:@@@@+@+:;@@@@@@@;:#';::'@@@@@@.  `::;,..`::+:,;@@@@@@:.``
`'@@@@@@'..```.,,....```  ``                    `                      ..:;@@@@@@@@+.
@;;;;@;,,`` ``                                                             `:@@@@@@:`
@@++';:,.```                                                                ``;+@#:,.
@@@@#+:.`         `,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@'@@@@@+:.                    `.:'::,
@@@@@@:,`...`,@@@@@@@@@@,    +@@@@@@@@@@@@@@@@@@@@@@@@`  `;'@@@@#               .,,,,
@@@@@@':::@@@@@@@@.`   `@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.    ``,@@@`           `.::,
@@@@@@#@@@@@';.    `@@@@@@@@;,@`@@@@@@@@@@@@@@@@@@@@@@@@@@@@@`   .,@@@@         ``..,
@@@@@@@@@:..    @@@@@,         ;@@@@@@@@@@@@@@@@@@  ,@@@@@:@@@@@   `,'@@@        ```.
@@@@@':,,`   @@@@:`            @@@@@@@@@@@@@@@@@@     ,@@: `:@@@@@; ..:@@@`       ```
@@@@;:`   @@@@@@..             '@@@@@@@@@@@@@@@@@@    `@@`    .@@@@@,`:'@@@.        `
@@@@;:.`@@@@@,   ``             @@@@@@@@@@@@@@@@@@@@@@@@@      ,@@@@@@.'@@@@,`
@@@+':''`  ;@@@@@@,,`            @@@@@@@@@@@@@@@@@@@@@@'       `.:@@@#@:@@@@':.
:;;;:@@,,.`  `@@@+,   `+.         @@@@@@@@@@@@@@@@@@@@`       ```.     @@:';,,,.`
.,,,,,,;;+;:.`..;,.,      ,,`       @@@@@@@@@@@@@@@@`       ```     ,@@,    ``` `
`......,,;+++#';@@@@@@.                  '@@@@@@;      ```     .;@@@@.
 ```` `,;'+@@+;:'@@@'@@@@@:.                `             ,#@@@@+,
        .:+'@';::'@+':,;,#@@@@@@@@@@@@@@@@@@:      .@@@@@@@:
         `:,,::,.`...,,`..,,,,...,,,,,...`:;@@@@@@@@;
           `.....```` `,.`````````..,,,,,.....``````
*/

class PorousFlowDictator : public GeneralUserObject, public Coupleable
{
public:
  PorousFlowDictator(const InputParameters & parameters);

  virtual void initialize() override{};
  virtual void execute() override{};
  virtual void finalize() override{};

  /**
   * The number of PorousFlow variables.  Materials
   * and Kernels will calculate and use derivatives
   * with respect to these variables in the Jacobian
   */
  unsigned int numVariables() const;

  /// The number of fluid phases
  unsigned int numPhases() const;

  /// The number of fluid components
  unsigned int numComponents() const;

  /// The number of aqueous equilibrium secondary species
  unsigned int numAqueousEquilibrium() const;

  /// The number of aqueous kinetic secondary species
  unsigned int numAqueousKinetic() const;

  /// The aqueous phase number
  unsigned int aqueousPhaseNumber() const;

  /**
   * The PorousFlow variable number
   * @param moose_var_num the MOOSE variable number
   * eg if porous_flow_vars = 'pwater pgas', and the variables in
   * the simulation are 'energy pwater pgas shape'
   * then porousFlowVariableNum(2) = 1
   */
  unsigned int porousFlowVariableNum(unsigned int moose_var_num) const;

  /**
   * Returns true if moose_var_num is a porous flow variable
   * @param moose_var_num the MOOSE variable number
   * eg if porous_flow_vars = 'pwater pgas', and the variables in
   * the simulation are 'energy pwater pgas shape'
   * then isPorousFlowVariable(0) = false, isPorousFlowVariable(1) = true
   */
  bool isPorousFlowVariable(unsigned int moose_var_num) const;

  /**
   * Returns true if moose_var_num is not a porous flow variabe
   * @param moose_var_num the MOOSE variable number
   * eg if porous_flow_vars = 'pwater pgas', and the variables in
   * the simulation are 'energy pwater pgas shape'
   * then notPorousFlowVariable(0) = true, notPorousFlowVariable(1) = false
   */
  bool notPorousFlowVariable(unsigned int moose_var_num) const;

protected:
  /// Number of PorousFlow variables
  const unsigned int _num_variables;

  /// Number of fluid phases
  const unsigned int _num_phases;

  /// Number of fluid components
  const unsigned int _num_components;

  /// Number of aqueous-equilibrium secondary species
  const unsigned int _num_aqueous_equilibrium;

  /// Number of aqeuous-kinetic secondary species that are involved in mineralisation
  const unsigned int _num_aqueous_kinetic;

  /// Aqueous phase number
  const unsigned int _aqueous_phase_number;

private:
  /// _moose_var_num[i] = the moose variable number corresponding to porous flow variable i
  std::vector<unsigned int> _moose_var_num;

  /// _pf_var_num[i] = the porous flow variable corresponding to moose variable i
  std::vector<unsigned int> _pf_var_num;
};

#endif // POROUSFLOWDICTATOR_H
