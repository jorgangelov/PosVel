#ifndef MYMATH_H
#define MYMATH_H
#include <string.h>
#include <stdio.h>
#include <stdint.h>


template <uint8_t dim> class cVector
{
public:
  cVector()
  {
    memset(entries,0,sizeof(entries));
  }

  float& operator()(uint8_t _i);
  cVector<dim> operator+(cVector<dim>& _other);
  cVector<dim> operator*(float _f);

private:
float entries[dim];

};

template <uint8_t dim> cVector<dim> operator*(float _f,cVector<dim>& _vector);




template <uint8_t dim> float& cVector<dim>::operator()(uint8_t _i)
{
  return entries[_i-1];
}

template <uint8_t dim> cVector<dim> cVector<dim>::operator+(cVector<dim>& _other)
{
  cVector<dim> temp;
  for(int i=0; i<dim; i++)
  {
    temp.entries[i] = entries[i] + _other.entries[i];
  }

  return temp;
}

template <uint8_t dim> cVector<dim> cVector<dim>::operator*(float _f)
{
  cVector<dim> temp;
  for (int i=0; i<dim; i++)
  {
    temp.entries[i] = entries[i] * _f;
  }
  return temp;
}

template <uint8_t dim> cVector<dim> operator*(float _f, cVector<dim>& _vector)
{
  cVector<dim> temp;
  for (int i=0; i<dim; i++)
  {
    temp(i+1) = _vector(i+1) * _f;
  }
  return temp;
}




#endif
