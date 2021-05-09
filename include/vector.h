/**
 * @file    vector.h
 * @brief   Implementation of an sequencial container based o STL's vector
 * @author  Bruna Hellen de Castro Dantas Barbosa
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cstdlib> // size_t
#include <stdexcept> // std::out_of_range
#include <initializer_list> // std::initializer_list<>
#include <stdexcept>  // std::out_of_range


namespace sc
{

	template <typename T>
		class MyIterator
		{
			public:
				
				typedef std::ptrdiff_t difference_type;
				typedef T& reference;
				typedef T value_type;
				typedef T* pointer;
        /// Identificar a categoria do iterador para algoritmos do STL.
        typedef std::bidirectional_iterator_tag iterator_category;
			
			private:
				T * current; 
			
			public:
		
				/**
				 * @brief Construct a new My Iterator object
				 * 
				 * @param ptr 
				 */
				MyIterator(T * ptr = nullptr ): current(ptr){ /* empty */ }

				
				/**
				 * @brief Destroy the My Iterator object
				 * 
				 */
				~MyIterator() = default;

				/*	Operators	*/

				/**
				 * @brief as in *it : return a reference to the object located at the position pointed by the iterator. The reference may or may not be modifiable.
				 * 
				 * @return const T& 
				 */
				const T & operator* ( ) const{ return *current; }
				
				/**
				 * @brief 
				 * 
				 * @return pointer 
				 */
				pointer operator ->( void ) const { assert( current != nullptr ); return current; }
				
				/**
				 * @brief advances iterator to the next location within the list. We should provide both prefix and posfix form, or ++it and it++
				 * 
				 * @return MyIterator& 
				 */
				MyIterator & operator++( ){	current++;	return *this;	}
				
				/**
				 * @brief advances iterator to the next location within the list. We should provide both prefix and posfix form, or ++it and it++
				 * 
				 * @return MyIterator& 
				 */
				MyIterator & operator++( int )
				{
					MyIterator temp = *this;
					current++;

					return temp; // this
				}
				
				/**
				 * @brief reduces iterator to the previous location within the list. We should provide both prefix and posfix form, or --it and it--
				 * 
				 * @return MyIterator& 
				 */
				MyIterator & operator-- ( ){	current--;	return *this;	}
				
				/**
				 * @brief reduces iterator to the previous location within the list. We should provide both prefix and posfix form, or --it and it--
				 * 
				 * @return MyIterator& 
				 */
				MyIterator & operator--( int )
				{
					MyIterator temp = *this;
					current--;

					return temp; // this
				}

				/**
				 * @brief returns the iterator to position it+n, we should provide both prefix and posfix form it+n and n+it.
				 * 
				 * @param n 
				 * @param it 
				 * @return MyIterator 
				 */
				friend MyIterator operator +( difference_type n, MyIterator it){ return n+it.current; }
				
				/**
				 * @brief returns the iterator to position it+n, we should provide both prefix and posfix form it+n and n+it.
				 * 
				 * @param it 
				 * @param n 
				 * @return MyIterator 
				 */
				friend MyIterator operator +( MyIterator it, difference_type n){ return it.current+n; }
				
				/**
				 * @brief returns the iterator to position it-n, we should provide both prefix and posfix form it-n and n-it.
				 * 
				 * @param n 
				 * @param it 
				 * @return MyIterator 
				 */
				friend MyIterator operator -( difference_type n, MyIterator it){ return n-it.current;}
				
				/**
				 * @brief returns the iterator to position it-n, we should provide both prefix and posfix form it-n and n-it.
				 * 
				 * @param it 
				 * @param n 
				 * @return MyIterator 
				 */
				friend MyIterator operator -( MyIterator it, difference_type n){ return it.current-n;}

				/**
				 * @brief as in it1 == it2 : returns true if both iterators refer to the same location within the list, and false otherwise
				 * 
				 * @param rhs 
				 * @return true 
				 * @return false 
				 */
				bool operator== ( const MyIterator & rhs) const{ return current == rhs.current; }
				
				/**
				 * @brief as in it1 != it2 : returns true if both iterators refer to a different location within the list, and false otherwise.
				 * 
				 * @param rhs 
				 * @return true 
				 * @return false 
				 */
				bool operator != ( const MyIterator & rhs) const{ return current != rhs.current; }

			

		};

	template <typename T>
	class vector 
	{
		
		public:
			
			typedef size_t size_type;
			const static size_type DEFAULT_SIZE = 0;
			typedef T value_type ;
			typedef  MyIterator< T > Iterator; //See code 3
			typedef  MyIterator< const T > const_iterator ;// See Code 3 
			typedef T& reference;
			typedef const T& const_reference; 
			typedef T* pointer;

		private:
			size_type m_end; //<! Current list size (or index past-last valid elemen>
			size_type m_capacity; //<! List’s storage capacity.
			pointer m_storage; //<! Data storage area for the dynamic array.

		public:

//############################# [I] SPECIAL MEMBERS
			 
			//Constructors:
			 
			 /**
			  * @brief Constructs an empty container, with no elements.
			  * 
			  */
			 vector( ): m_end(0), m_capacity(DEFAULT_SIZE), m_storage(new value_type[m_capacity]){	/* Empty */	}

			 /**
			  * @brief Constructs a container with a copy of each of the elements in model, in the same order.
			  * 
			  * @param model 
			  */
			 vector(const vector & model):m_end(model.m_end), m_capacity(model.m_capacity), m_storage(new value_type[m_capacity])
			 {
			 	for(auto i(0u); i != m_end; ++i)
			 	{
					m_storage[i] = model.m_storage[i];
			 	}
			 }

			 
			 /**
			  * @brief Constructs a container with capacity equal to n
			  * 
			  * @param n 
			  */
			 vector(size_type n): m_end(0), m_capacity(n), m_storage (new value_type[m_capacity]){ /* Empty */ }

			 /**
			  * @brief  Constructs a container with as many elements as the range [first,last), with each element 
				* constructed from its corresponding element in that range, in the same order.
			  * @param first 
			  * @param last 
			  * @return template < typename InputItr > 
			  */
			 template < typename InputItr >
			 vector( InputItr first, InputItr last)
			 {
			 	size_type dist(0);
			 	auto r = first;

			 	while( r != last){	dist++; r++;	}

			 	m_end = dist;
				m_capacity= dist;
				m_storage = new value_type[m_capacity];

				auto it(first);

				for (auto i(0u); i < dist; ++i, ++it)
				{
					m_storage[i] = *it;
				}

			 }

			 
			 /**
			  * @brief Construct a new vector object
			  * 
			  * @param ilist 
			  */
			 /*		Constructor from  initializer List 	*/
			 
			 vector(std::initializer_list<T>  ilist):
			 	vector(ilist.size())
			 {
			 	m_end = ilist.size();
			 	auto count(0);
			 	
			 	for (auto &element : ilist)
				{
					m_storage[count] = element;
					++count;
				}
			 } 

			/**
			 * @brief Destroys the object
			 * 
			 */
			 //Destructor:
			 ~vector( ) {	delete [] m_storage;	}
			 
			 /**
			  * @brief Assigns new contents to the container, replacing its current contents,
				*  and modifying its size accordingly.
			  * 
			  * @param model a vector object of the same type
			  * @return vector&  
			  */
			 vector & operator= ( const vector & model)
			 {
			 	m_end = model.m_end;
			 	m_capacity = model.m_capacity;
			 	m_storage = new value_type[m_capacity];

			 	for (auto i(0u); i != m_end; ++i){	m_storage[i] = model.m_storage[i];	}

			 	return *this;
			 }


//############################# [II] IteratorS
			 
			 /**
			  * @brief Return iterator to beginning
			  * 
			  * @return Iterator 
			  */
			 Iterator begin( void ){	return Iterator(&m_storage[0]);	}
			 
			 /**
			  * @brief Return iterator to the end
			  * 
			  * @return Iterator 
			  */
			 Iterator end( void ){	return Iterator(&m_storage[m_end]);	}
			 
			 /**
			  * @brief Return const_iterator to beginning
			  * 
			  * @return const_iterator 
			  */
			 const_iterator cbegin( void ) const{	return const_iterator(&m_storage[0]); }
			 
			 /**
			  * @brief Return const_iterator to the end
			  * 
			  * @return const_iterator 
			  */
			 const_iterator cend( void ) const{		return const_iterator(&m_storage[0]); }

//############################# [III] Capacity
			 
			 /**
			  * @brief Returns the number of elements in the vector.
			  * 
			  * @return size_type 
			  */
			 size_type size( void ) const{	return m_end;	}
			 
			 /**
			  * @brief Return size of allocated storage capacity
			  * 
			  * @return size_type 
			  */
			 size_type capacity( void ) const{	return m_capacity;	}
			 
			 /**
			  * @brief Test whether vector is empty
			  * 
			  * @return true 
			  * @return false 
			  */
			 bool empty( void ) const{	return m_end == 0;	}


//############################# [IV] Modifiers
			 
			 /**
			  * @brief Removes all elements from the vector (which are destroyed), 
				* leaving the container with a size of 0.
			  * 
			  */
			 void clear( void )
			 {
			 	delete [] m_storage;
				m_end = 0;
				m_storage = nullptr; //Because the object doesn't stop existing is just cleared

			 }

			 /**
			  * @brief Adds a new element at the begginng of the vector, before its current first element. 
				* The content of ref is copied and the other are moved .
			  * 
			  * @param ref 
			  */
			 void push_front( const_reference ref)
			 {
			 	
				 if( m_end == m_capacity ){	reserve(m_capacity * 2);}
					
			 	 for(auto i= m_end+1; i != 0; --i)
			 	 {
			 	 	m_storage[i] = m_storage[i-1];
			 	 }
								m_end++;
                m_storage[0] = ref;
			 }

			 /**
			  * @brief Adds a new element at the end of the vector, 
				* after its current last element. The content of ref is copied (or moved) to the new element
			  * 
			  * @param ref 
			  */
			 void push_back( const_reference ref)
			 {
				
				 if( m_end == m_capacity ){	reserve( 2 * m_capacity);}
				  
					m_end++;
					m_storage[m_end] = ref; 
			 }

			 /**
			  * @brief Removes the last element in the vector, effectively reducing the container size by one.
			  * 
			  */
			 void pop_back( void )
			 {
			 	if( empty() ){	throw std::out_of_range("Can't pop out of an empty vector \n");}
				
				m_storage[--m_end];
			 }

			 /**
			  * @brief Removes the first element in the vector, effectively reducing the container size by one and moving the remaining ones
			  * 
			  */
			 void pop_front( void )
			 {
			 	if(empty()){	throw std::out_of_range("Can't pop out of an empty vector \n");}
				 for(auto i(0u); i != m_end; ++i){	m_storage[i] = m_storage[i+1];}
                m_end--;
			 }
			 
			 /**
			  * @brief The vector is extended by inserting new elements before the element at the specified position, 
				* effectively increasing the container size by the number of elements inserted.
			  * @param first 
			  * @param ref 
			  * @return Iterator 
			  */
			 Iterator insert( Iterator position, const_reference ref)
			 {
				 
				  auto first = begin();
					unsigned int count = 0;

					for(count = 0; first != position; ++first, ++count);

					if(m_end == m_capacity){ reserve(m_capacity*2); }

					for(auto i(m_end+1); i != count; i--)
					{
						for( auto i(m_end+1); i != count; --i ){ m_storage[i] = m_storage[i-1]; }
					} 

					m_storage[count] = ref;
					m_end++;

					return first;
			 }
			 
			 /**
			  * @brief The vector is extended by inserting new elements before the element at the specified position, 
				* effectively increasing the container size by the number of elements inserted.
			  * 
			  * @tparam InputItr 
			  * @param position 
			  * @param first 
			  * @param last 
			  * @return Iterator 
			  */
			 template < typename InputItr >
			 Iterator insert( Iterator  position, InputItr first, InputItr last);
			 
			 /**
			  * @brief The vector is extended by inserting new elements before the element at the specified position, 
				* effectively increasing the container size by the number of elements inserted.
			  * 
			  * @return Iterator 
			  */
			 Iterator insert( Iterator position, std::initializer_list< value_type > );
			 
			 /**
			  * @brief Requests that the vector capacity be at least enough to contain n_size elements.
			  * 
			  * @param n_size 
			  */
			 void reserve(size_type n_size)
			 {
			 	if(n_size < m_capacity){ return;} //If the capacity asked is smaller than the current one, nothing is done.

			 	pointer temporary =  new value_type[n_size];

			 	for(auto i(0u); i < m_capacity; i++){	temporary[i] = m_storage[i];} 

			 	delete [] m_storage;
				m_capacity = n_size;
				m_storage = temporary;
				

			 }
			 
			 /**
			  * @brief Requests the container to reduce its capacity to fit its size.
			  * 
			  */
			 void shrink_to_fit( void )
			 {
			 	pointer temporary = new value_type[m_end];  
				
				for(auto i(0); i < m_end; ++i){	temporary[i] = m_storage[i];}

				delete [] m_storage;
				m_storage = temporary;
				m_capacity = m_end;
			 }
			 /**
			  * @brief Assigns the value of ref to the entire vector object, changing it's size
			  * 
			  * @param reference 
			  */
			 void assign( size_type count, const_reference ref)
			 {
				  	if(count > m_capacity){ reserve(count); }
				 		
							m_end = count;
						
								for(auto i(0u); i < count; ++i){	m_storage[i] = ref;	}	
						
			 }
			 
			 /**
			  * @brief In the initializer list assign, the new contents are copies of the values passed as initializer list, in the same order.
			  * 
			  * @param ilist 
			  */
			 void assign( std::initializer_list<T>  ilist)
			 {
			 		if(empty()) {throw std::out_of_range("Can't assign values to an empty vector. \n");}
			
								 	auto count = 0;
									size_type i = 0;

									while(count < m_end)
									{ 
			 							for (auto &element : ilist)
										{
												m_storage[i] = element;
												i++;
												count++;
										}
										
									}
			 }

			 /**
			  * @brief In the range assign, the new contents are elements constructed from each of the elements in the range between first and last, in the same order.
			  * 
			  * @tparam InputItr 
			  * @param first 
			  * @param last 
			  */
			 template < typename InputItr >
			 void assign( InputItr first, InputItr last)
			 {
				
			 	size_type dist = 0;
			 	auto right = first;

			 	while( right != last){	dist++; right++;	}
			  
			 	m_end = dist;
				m_capacity = dist;
				m_storage = new T[m_capacity];

				auto value = first;

				for (auto i(0u); i < dist; ++i, ++value)
				{
					m_storage[i] = *value;
				}
		
			 } 
			 
			 /**
			  * @brief Removes from the vector a range of elements ([first,last)).This effectively reduces the container size by the number of elements removed, which are destroyed.
			  * 
			  * @param first 
			  * @param last 
			  * @return Iterator 
			  */
			 Iterator erase( Iterator first, Iterator last){}
			 
			 /**
			  * @brief Removes from the vector either a single element (position).This effectively reduces the container size by the number of elements removed, which are destroyed.
			  * 
			  * @param position 
			  * @return Iterator 
			  */
			 Iterator erase( Iterator position)
			 {
				
			 	auto first = begin(); 
				int count = 0;

				 while (position != first)
				 {
					  ++first;
						++count;
				 }

				 for (auto i = count; i < m_end-1; i++)
				 {
					  m_storage[i] = m_storage[i+1];
				 }
				 
				 m_end--;

					 return Iterator(first);

			 	
				
			 	} 

			 	//return Iterator(posi);

//#############################  [V] Element access ##################################################################################################
			 
			 /**
			  * @brief Returns a const_reference to the last element in the vector.
			  * 
			  * @return const_reference 
			  */
			 const_reference back( void ) const
			 {	 
				 	if(empty()){	throw std::out_of_range("The vector is empty :( \n");}
				 		return m_storage[m_end-1];
			 }

			 /**
			  * @brief Returns a reference to the last element in the vector.
			  * 
			  * @return reference 
			  */
			 reference back(void)
			 {
 					if(empty()){	throw std::out_of_range("The vector is empty :( \n");}
					 return m_storage[m_end-1];
			 }

			 /**
			  * @brief Returns a reference to the first element in the vector.
			  * 
			  * @return reference 
			  */
			 reference front( void ) 
			 {	
				 if(empty()){	throw std::out_of_range("The vector is empty :(\n");}
				 	return m_storage[0];
			 }
			 
			 /**
			  * @brief Returns a const_reference to the first element in the vector.
			  * 
			  * @return const_reference 
			  */
			 const_reference front( void ) const
			 {	
				 if(empty()){	throw std::out_of_range("The vector is empty :(\n");}
				 	return m_storage[0];
			 }
	     /**
	      * @brief Returns a const_reference to the element at position n in the vector container.
	      * 
	      * @param posi 
	      * @return const_reference 
	      */
			 const_reference operator[]( size_type posi) const{	 return m_storage[posi];}
			 
			 /**
			  * @brief Returns a reference to the element at position n in the vector.
			  * 
			  * @param n 
			  * @return reference 
			  */
			 reference operator[]( size_type n)
			 {
				 if(n >= m_end){	throw std::out_of_range("This element is out of range.\n");	}	
				 
				 return m_storage[n];
			 }
			 
			 /**
			  * @brief Returns a const_reference to the element at position n in the vector.
			  * 
			  * @param n 
			  * @return const_reference 
			  */
			 const_reference at( size_type n) const
			 {
			 	//adcionar condição pra não pegar do m_end pra cima, que é fora do range lesa
			 	if(n >= m_end){	throw std::out_of_range("This element is out of range.\n");	}
			 	
			 	return m_storage[n]; 
			 }
			 
			 /**
			  * @brief Returns a reference to the element at position n in the vector.
			  * 
			  * @param n
			  * @return reference 
			  */
			 reference at( size_type n)
			 {	
			 	//adcionar condição pra não pegar do m_end pra cima, que é fora do range lesa
			 	if(n >= m_end){	throw std::out_of_range("This element is out of range.\n");	}
			 	
			 	return m_storage[n];
			 }
			 
			 /**
			  * @brief Returns a direct pointer to the memory array used internally by the vector to store its owned elements.
			  * 
			  * @return pointer 
			  */
			 pointer data( void ){	return m_storage;}
			 
			 /**
			  * @brief Returns a const_reference to the memory array used internally by the vector to store its owned elements.
			  * 
			  * @return const_reference 
			  */
			 const_reference data( void ) const{	return m_storage;}

//############################# [VI] Operators ##################################################################################################
				
				/**
				 * @brief Checks if the contents of two vectors are equal, that is, their size and content.
				 * 
				 * @param test_v 
				 * @return true 
				 * @return false 
				 */
		    bool operator== ( const vector& test_v)const
		    {	
		    	if (this->m_end == test_v.m_end)
		    	{
		    		auto count(0);
			    	for (int i = 0; i < this->m_end; ++i)
			    	{
			    		if(this->m_storage[i] == test_v.m_storage[i]){ count++; }
			    	}

		    		return count == this->m_end;
		    	}
		    	else
		    	{
		    		return this->m_end == test_v.m_end;
		    	}

		    }
		    
				/**
				 * @brief Checks if the contents of two vectors are different, that is, their size and content.
				 * 
				 * @param test_v 
				 * @return true 
				 * @return false 
				 */
		    bool operator!= ( const vector& test_v)const 
		    {
		    	if((this->m_capacity != test_v.m_capacity) || (this->m_end != test_v.m_end)){ return true;}
		    	
					for(auto i(0u); i != m_end; i++)
					{
						if(m_storage[i] != test_v.m_storage[i])
						{
							return true;
						}
					}
						return false;
				
		    }

	       // [VII] Friend functions.
		    /*
			friend std::ostream & operator <<( std::ostream & os_, const vector<T> & v_ );
			friend void swap( vector<T> & first_, vector<T> & second_ ); */


	};
};

#endif