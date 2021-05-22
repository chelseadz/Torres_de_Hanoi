/*****************************************************************//**
 * \file   Utileria.tpp
 * \brief  Funciones templete de utileria.h
 * 
 * \author Equipo Rocket
 * \date   22/05/2021
 *********************************************************************/

template < class T>
void Quicksort(T arr[], int start, int end) {

	if (start == end - 1) {
		if (arr[end] < arr[start]) {
			std::swap(arr[start], arr[end]);
		}
	}
	else if (start < end) {

		T piv;

		piv = Median_of_three(arr[start], arr[end], arr[(end + start) / 2]);

		int i, j;

		i = start, j = end;

		while (i < j) {
			while (arr[i] < piv) ++i;
			while (piv < arr[j]) --j;

			if (j < i) break;
			if (i != j) {
				std::swap(arr[i], arr[j]);

			}
			++i, --j;
		}

		if (j > start) Quicksort(arr, start, j);
		if (i < end) Quicksort(arr, i, end);

	}
}

template < class T >
T Median_of_three(T i, T j, T k) {
	if (!(i < j)) {
		if (j < k) return j;
		else {
			if (k < i) return i;
			return k;
		}
	}
	else {
		if (k < i) {
			if (k < j) return j;
			return k;
		}
		return i;
	}
}