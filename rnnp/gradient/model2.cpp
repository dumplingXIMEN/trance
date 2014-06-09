//
//  Copyright(C) 2014 Taro Watanabe <taro.watanabe@nict.go.jp>
//

#include "gradient/model2.hpp"

namespace rnnp
{
  namespace gradient
  {
    
    void Model2::initialize(const size_type& hidden,
			    const size_type& embedding)
    {

      Gradient::initialize(hidden, embedding);
    
      terminal_.clear();
    
      // initialize matrix    
      Wc_.clear();
    
      Wsh_.clear();
      Bsh_.clear();
    
      Wrel_.clear();
      Brel_.clear();

      Wrer_.clear();
      Brer_.clear();
      
      Wu_.clear();
      Bu_.clear();
      
      Wf_ = tensor_type::Zero(hidden_, hidden_);
      Bf_ = tensor_type::Zero(hidden_, 1);
    
      Wi_ = tensor_type::Zero(hidden_, hidden_);
      Bi_ = tensor_type::Zero(hidden_, 1);
    
      Ba_ = tensor_type::Zero(hidden_, 1);
    }

#define GRADIENT_STREAM_OPERATOR(Theta, Op, Stream)	\
    Theta.Op(Stream, Theta.terminal_);			\
							\
    Theta.Op(Stream, Theta.Wc_);			\
							\
    Theta.Op(Stream, Theta.Wsh_);			\
    Theta.Op(Stream, Theta.Bsh_);			\
							\
    Theta.Op(Stream, Theta.Wrel_);			\
    Theta.Op(Stream, Theta.Brel_);			\
							\
    Theta.Op(Stream, Theta.Wrer_);			\
    Theta.Op(Stream, Theta.Brer_);			\
							\
    Theta.Op(Stream, Theta.Wu_);			\
    Theta.Op(Stream, Theta.Bu_);			\
							\
    Theta.Op(Stream, Theta.Wf_);			\
    Theta.Op(Stream, Theta.Bf_);			\
							\
    Theta.Op(Stream, Theta.Wi_);			\
    Theta.Op(Stream, Theta.Bi_);			\
							\
    Theta.Op(Stream, Theta.Bi_);

    std::ostream& operator<<(std::ostream& os, const Model2& theta)
    {
      os.write((char*) &theta.hidden_,    sizeof(theta.hidden_));
      os.write((char*) &theta.embedding_, sizeof(theta.embedding_));
      os.write((char*) &theta.count_,     sizeof(theta.count_));

      GRADIENT_STREAM_OPERATOR(theta, write_matrix, os);
    
      return os;
    }
  
    std::istream& operator>>(std::istream& is, Model2& theta)
    {
      is.read((char*) &theta.hidden_,    sizeof(theta.hidden_));
      is.read((char*) &theta.embedding_, sizeof(theta.embedding_));
      is.read((char*) &theta.count_,     sizeof(theta.count_));

      GRADIENT_STREAM_OPERATOR(theta, read_matrix, is);
    
      return is;
    }

#undef GRADIENT_STREAM_OPERATOR

#define GRADIENT_BINARY_OPERATOR(Op)	\
    Op(terminal_, x.terminal_);			\
						\
    Op(Wc_, x.Wc_);				\
						\
    Op(Wsh_, x.Wsh_);				\
    Op(Bsh_, x.Bsh_);				\
						\
    Op(Wrel_, x.Wrel_);				\
    Op(Brel_, x.Brel_);				\
						\
    Op(Wrer_, x.Wrer_);				\
    Op(Brer_, x.Brer_);				\
						\
    Op(Wu_, x.Wu_);				\
    Op(Bu_, x.Bu_);				\
						\
    Op(Wf_, x.Wf_);				\
    Op(Bf_, x.Bf_);				\
						\
    Op(Wi_, x.Wi_);				\
    Op(Bi_, x.Bi_);				\
						\
    Op(Ba_, x.Ba_);

  
    Model2& Model2::operator+=(const Model2& x)
    {
      GRADIENT_BINARY_OPERATOR(plus_equal);

      return *this;
    }
  
    Model2& Model2::operator-=(const Model2& x)
    {
      GRADIENT_BINARY_OPERATOR(minus_equal);

      return *this;
    }

#undef GRADIENT_BINARY_OPERATOR

  };
};
