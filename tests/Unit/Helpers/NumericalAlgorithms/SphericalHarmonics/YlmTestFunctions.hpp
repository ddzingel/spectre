// Distributed under the MIT License.
// See LICENSE.txt for details.

#pragma once

#include <array>
#include <cmath>
#include <cstddef>
#include <vector>

#include "DataStructures/DataVector.hpp"
#include "NumericalAlgorithms/SphericalHarmonics/YlmSpherepack.hpp"
#include "Utilities/Gsl.hpp"

namespace YlmTestFunctions {

using SecondDeriv = YlmSpherepack::SecondDeriv;

class ScalarFunctionWithDerivs {
 public:
  virtual ~ScalarFunctionWithDerivs() = default;
  ScalarFunctionWithDerivs() = default;
  ScalarFunctionWithDerivs(const ScalarFunctionWithDerivs&) = default;
  ScalarFunctionWithDerivs(ScalarFunctionWithDerivs&&) = default;
  ScalarFunctionWithDerivs& operator=(const ScalarFunctionWithDerivs&) =
      default;
  ScalarFunctionWithDerivs& operator=(ScalarFunctionWithDerivs&&) = default;
  virtual void func(gsl::not_null<DataVector*> u, size_t stride, size_t offset,
                    const std::vector<double>& thetas,
                    const std::vector<double>& phis) const = 0;
  virtual void dfunc(gsl::not_null<std::array<double*, 2>*> du, size_t stride,
                     size_t offset, const std::vector<double>& thetas,
                     const std::vector<double>& phis) const = 0;
  virtual void ddfunc(gsl::not_null<SecondDeriv*> ddu, size_t stride,
                      size_t offset, const std::vector<double>& thetas,
                      const std::vector<double>& phis) const = 0;
  virtual void scalar_laplacian(gsl::not_null<DataVector*> slap, size_t stride,
                                size_t offset,
                                const std::vector<double>& thetas,
                                const std::vector<double>& phis) const = 0;
  virtual double integral() const = 0;
};

class Y00 : public ScalarFunctionWithDerivs {
 public:
  ~Y00() override = default;
  Y00() = default;
  Y00(const Y00&) = default;
  Y00(Y00&&) = default;
  Y00& operator=(const Y00&) = default;
  Y00& operator=(Y00&&) = default;
  void func(gsl::not_null<DataVector*> u, size_t stride, size_t offset,
            const std::vector<double>& thetas,
            const std::vector<double>& phis) const override;
  void dfunc(gsl::not_null<std::array<double*, 2>*> du, size_t stride,
             size_t offset, const std::vector<double>& thetas,
             const std::vector<double>& phis) const override;
  void ddfunc(gsl::not_null<SecondDeriv*> ddu, size_t stride, size_t offset,
              const std::vector<double>& thetas,
              const std::vector<double>& phis) const override;
  void scalar_laplacian(gsl::not_null<DataVector*> slap, size_t stride,
                        size_t offset, const std::vector<double>& thetas,
                        const std::vector<double>& phis) const override;
  double integral() const override { return sqrt(4.0 * M_PI); }
};

class Y10 : public ScalarFunctionWithDerivs {
 public:
  ~Y10() override = default;
  Y10() = default;
  Y10(const Y10&) = default;
  Y10(Y10&&) = default;
  Y10& operator=(const Y10&) = default;
  Y10& operator=(Y10&&) = default;
  void func(gsl::not_null<DataVector*> u, size_t stride, size_t offset,
            const std::vector<double>& thetas,
            const std::vector<double>& phis) const override;
  void dfunc(gsl::not_null<std::array<double*, 2>*> du, size_t stride,
             size_t offset, const std::vector<double>& thetas,
             const std::vector<double>& phis) const override;
  void ddfunc(gsl::not_null<SecondDeriv*> ddu, size_t stride, size_t offset,
              const std::vector<double>& thetas,
              const std::vector<double>& phis) const override;
  void scalar_laplacian(gsl::not_null<DataVector*> slap, size_t stride,
                        size_t offset, const std::vector<double>& thetas,
                        const std::vector<double>& phis) const override;
  double integral() const override { return 0.0; }
};

// Im(Y11(theta,phi))
class Y11 : public ScalarFunctionWithDerivs {
 public:
  ~Y11() override = default;
  Y11() = default;
  Y11(const Y11&) = default;
  Y11(Y11&&) = default;
  Y11& operator=(const Y11&) = default;
  Y11& operator=(Y11&&) = default;
  void func(gsl::not_null<DataVector*> u, size_t stride, size_t offset,
            const std::vector<double>& thetas,
            const std::vector<double>& phis) const override;
  void dfunc(gsl::not_null<std::array<double*, 2>*> du, size_t stride,
             size_t offset, const std::vector<double>& thetas,
             const std::vector<double>& phis) const override;
  void ddfunc(gsl::not_null<SecondDeriv*> ddu, size_t stride, size_t offset,
              const std::vector<double>& thetas,
              const std::vector<double>& phis) const override;
  void scalar_laplacian(gsl::not_null<DataVector*> slap, size_t stride,
                        size_t offset, const std::vector<double>& thetas,
                        const std::vector<double>& phis) const override;
  double integral() const override { return 0.0; }
};

class SimpleScalarFunction {
 public:
  virtual ~SimpleScalarFunction() = default;
  SimpleScalarFunction() = default;
  SimpleScalarFunction(const SimpleScalarFunction&) = default;
  SimpleScalarFunction(SimpleScalarFunction&&) = default;
  SimpleScalarFunction& operator=(const SimpleScalarFunction&) = default;
  SimpleScalarFunction& operator=(SimpleScalarFunction&&) = default;
  virtual DataVector func(const std::vector<double>& thetas,
                          const std::vector<double>& phis) const = 0;
};

// Re Y(10,10) + Im Y(10,7) + Re Y(6,2)
class FuncA : public SimpleScalarFunction {
 public:
  ~FuncA() override = default;
  FuncA() = default;
  FuncA(const FuncA&) = default;
  FuncA(FuncA&&) = default;
  FuncA& operator=(const FuncA&) = default;
  FuncA& operator=(FuncA&&) = default;
  DataVector func(const std::vector<double>& thetas,
                  const std::vector<double>& phis) const override;
};

// Im Y(10,7)+ Re Y(6,2)
class FuncB : public SimpleScalarFunction {
 public:
  ~FuncB() override = default;
  FuncB() = default;
  FuncB(const FuncB&) = default;
  FuncB(FuncB&&) = default;
  FuncB& operator=(const FuncB&) = default;
  FuncB& operator=(FuncB&&) = default;
  DataVector func(const std::vector<double>& thetas,
                  const std::vector<double>& phis) const override;
};

// Re Y(6,2)
class FuncC : public SimpleScalarFunction {
 public:
  ~FuncC() override = default;
  FuncC() = default;
  FuncC(const FuncC&) = default;
  FuncC(FuncC&&) = default;
  FuncC& operator=(const FuncC&) = default;
  FuncC& operator=(FuncC&&) = default;
  DataVector func(const std::vector<double>& thetas,
                  const std::vector<double>& phis) const override;
};

}  // namespace YlmTestFunctions
