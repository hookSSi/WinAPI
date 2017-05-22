#include "Object.h"

unsigned int Object::counter = 0;

const Vector2D& Object::GetSize() const  { return this->size; } // ũ�� 2D���͸� ������
const Vector2D& Object::GetPivot() const  { return this->pivot; } // �Ǻ� 2D���͸� ������

bool Object::SetSize(Vector2D& size) { this->size = size; pivot = size / 2; return true; }
bool Object::SetPivot(Vector2D& pivot) { this->pivot = pivot; return true; }