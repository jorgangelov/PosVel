#ifndef MYMATH_H
#define MYMATH_H
#include <string.h>
#include <stdio.h>
#include <stdint.h>

// Declarations
template <uint8_t dim> class cVector
{
public:
  cVector()
  {
    memset(entries,0,sizeof(entries));
  }

  float& operator()(uint8_t _i);
  cVector<dim> operator+(cVector<dim> _other);
  cVector<dim> operator*(float _f);
  float entries[dim];

};

template <uint8_t dim> cVector<dim> operator*(float _f,cVector<dim> _vector);
template <uint8_t dim> float operator*(cVector<dim> v1, cVector<dim> v2);
template <uint8_t dim> cVector<dim> operator-(cVector<dim> v1, cVector<dim> v2);

  

// Definitions
template <uint8_t dim> inline float& cVector<dim>::operator()(uint8_t _i)
{
  return entries[_i-1];
}

template <uint8_t dim> inline cVector<dim> cVector<dim>::operator+(cVector<dim> _other)
{
  cVector<dim> temp;
  for(int i=0; i<dim; i++)
  {
    temp.entries[i] = entries[i] + _other.entries[i];
  }

  return temp;
}

template <uint8_t dim> inline cVector<dim> cVector<dim>::operator*(float _f)
{
  cVector<dim> temp;
  for (int i=0; i<dim; i++)
  {
    temp.entries[i] = entries[i] * _f;
  }
  return temp;
}

template <uint8_t dim> inline cVector<dim> operator*(float _f, cVector<dim> _vector)
{
  cVector<dim> temp;
  for (int i=0; i<dim; i++)
  {
    temp(i+1) = _vector.entries[i] * _f;
  }
  return temp;
}


template <uint8_t dim> inline float operator*(cVector<dim> v1, cVector<dim> v2)
{
    float scalar = 0;
    for (int i=0; i<dim; i++)
    {
        scalar += v1.entries[i]*v2.entries[i];
    }
    return scalar;
}

template <uint8_t dim> inline cVector<dim> operator-(cVector<dim> v1, cVector<dim> v2)
{
    return v1 + (-1)*v2;
}


#endif
