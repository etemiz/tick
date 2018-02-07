#ifndef LIB_INCLUDE_TICK_ROBUST_MODEL_MODIFIED_HUBER_H_
#define LIB_INCLUDE_TICK_ROBUST_MODEL_MODIFIED_HUBER_H_

// License: BSD 3 clause

#include "tick/base_model/model_generalized_linear.h"
#include "tick/base_model/model_lipschitz.h"

#include <cereal/types/base_class.hpp>

template <class T>
class DLL_PUBLIC TModelModifiedHuber
    : public virtual TModelGeneralizedLinear<T>,
      public TModelLipschitz<T> {
 protected:
  using TModelGeneralizedLinear<T>::features_norm_sq;
  using TModelGeneralizedLinear<T>::compute_features_norm_sq;
  using TModelGeneralizedLinear<T>::n_samples;
  using TModelGeneralizedLinear<T>::n_features;
  using TModelGeneralizedLinear<T>::fit_intercept;
  using TModelGeneralizedLinear<T>::compute_grad_i;
  using TModelGeneralizedLinear<T>::n_threads;
  using TModelGeneralizedLinear<T>::get_inner_prod;
  using TModelLipschitz<T>::ready_lip_consts;
  using TModelLipschitz<T>::lip_consts;

 public:
  using TModelGeneralizedLinear<T>::get_label;
  using TModelGeneralizedLinear<T>::grad_i;
  using TModelGeneralizedLinear<T>::get_features;
  using TModelGeneralizedLinear<T>::grad_i_factor;

 public:
  TModelModifiedHuber(const std::shared_ptr<BaseArray2d<T>> features,
                      const std::shared_ptr<SArray<T>> labels,
                      const bool fit_intercept, const int n_threads = 1);

  const char *get_class_name() const override;

  T loss_i(const ulong i, const Array<T> &coeffs) override;

  T grad_i_factor(const ulong i, const Array<T> &coeffs) override;

  void compute_lip_consts() override;

  template <class Archive>
  void serialize(Archive &ar) {
    ar(cereal::make_nvp("ModelGeneralizedLinear",
                        cereal::base_class<TModelGeneralizedLinear<T>>(this)));
    ar(cereal::make_nvp("ModelLipschitz",
                        cereal::base_class<TModelLipschitz<T>>(this)));
  }
};

using ModelModifiedHuber = TModelModifiedHuber<double>;

using ModelModifiedHuberDouble = TModelModifiedHuber<double>;
CEREAL_SPECIALIZE_FOR_ALL_ARCHIVES(ModelModifiedHuberDouble,
                                   cereal::specialization::member_serialize)
using ModelModifiedHuberFloat = TModelModifiedHuber<float>;
CEREAL_SPECIALIZE_FOR_ALL_ARCHIVES(ModelModifiedHuberFloat,
                                   cereal::specialization::member_serialize)

#endif  // LIB_INCLUDE_TICK_ROBUST_MODEL_MODIFIED_HUBER_H_
