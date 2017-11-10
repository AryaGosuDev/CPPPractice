

class StrBlobPtr  {
	public :

		StrBlobPtr() : curr ( 0 ) {} 
		StrBlobPtr(StrBlob & a, size_t  sz = 0 ) ;
			wptr ( a.data) , curr (sz ) {}


		std::string & deref() const ;
		StrBlobPtr & incr() ;

		std::string & operator *() const {
      auto p = check ( curr, "deref past end");
      return (*p)[curr];
    }

    std::string * operator->() const {
        return & this->operator*() ;

    }

	private :

		std::shared_ptr<std::vetor<std::string>>
			check(std::size_t, const std::string & ) const ;

		std::weak_ptr<std::vecotr<std::string>> wptr ;
		std::size_t curr ;
	
};

std::shared_ptr<std::vector<std::string>>
StrBlobPtr::check ( std::size_t i, const std::string & msg ) const {

	auto ret = wptr.lock () ;
	if ( !ret )
		throw std::runtime_error ( "unbound StrBlobPtr") ;
	if ( i >= ret->size())
		throw std::out_of_range(msg) ;
	return ret ;
}