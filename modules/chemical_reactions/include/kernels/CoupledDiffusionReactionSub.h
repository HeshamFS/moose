/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef COUPLEDDIFFUSIONREACTIONSUB_H
#define COUPLEDDIFFUSIONREACTIONSUB_H

#include "Kernel.h"

class CoupledDiffusionReactionSub;

template <>
InputParameters validParams<CoupledDiffusionReactionSub>();

/**
 * Diffusion of primary species in given equilibrium species
 */
class CoupledDiffusionReactionSub : public Kernel
{
public:
  CoupledDiffusionReactionSub(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
  /// Material property of dispersion-diffusion coefficient
  const MaterialProperty<Real> & _diffusivity;
  /// Weight of the equilibrium species concentration in the total primary species concentration
  const Real _weight;
  /// Equilibrium constant for the equilibrium species in association form
  const Real _log_k;
  /// Stoichiometric coefficient of the primary species
  const Real _sto_u;
  /// Stoichiometric coefficients of the coupled primary species
  const std::vector<Real> _sto_v;
  /// Coupled primary species variable numbers
  std::vector<unsigned int> _vars;
  /// Coupled primary species concentrations
  std::vector<const VariableValue *> _vals;
  /// Coupled gradients of primary species concentrations
  std::vector<const VariableGradient *> _grad_vals;
  /// Activity coefficient of primary species in the equilibrium species
  const VariableValue & _gamma_u;
  /// Activity coefficients of coupled primary species in the equilibrium species
  std::vector<const VariableValue *> _gamma_v;
  /// Activity coefficient of equilibrium species
  const VariableValue & _gamma_eq;
};

#endif // COUPLEDDIFFUSIONREACTIONSUB_H
