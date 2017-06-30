#ifndef __ccipdMacros_h
#define __ccipdMacros_h






//////////////////////////////////////////////////////////////////////////////////////////
/**
* This is a very lightweight file containing
* some macros for commonly used 
* C++ code.
*/
//////////////////////////////////////////////////////////////////////////////////////////


/*
    #pragma warning is not recognized on Linux
*/

#if defined _MSC_VER

    #define ccipdDisableAllWarnings __pragma(warning( push, 0 ))

    #define ccipdEnableAllWarnings __pragma(warning( pop ))

#elif defined __GNUC__

    #define ccipdDisableAllWarnings \
    _Pragma("GCC diagnostic push")  \
    _Pragma("GCC diagnostic ignored \"-Wall\"")

    #define ccipdEnableAllWarnings _Pragma("GCC diagnostic pop")

#else /* add more compilers here */

#endif


ccipdDisableAllWarnings
#include <memory>
#include <string>
#include <cstddef> 
#include <iostream>
#include <itkMacro.h> 
//ccipdEnableAllWarnings



/**
* \brief declares CCIPD QApplication
*/
#define ccipdQApplicationDeclationMacro(argc, argv, projectName)      \
QApplication app(argc, argv);                                         \
QCoreApplication::setOrganizationName("CCIPD");                       \
QCoreApplication::setOrganizationDomain("http://ccipd.case.edu");     \
QCoreApplication::setApplicationName(projectName);                       
//////////////////////////////////////////////////////////////////////////////////////////
/**
* \brief Constructor/destructor declarations
*/
#define ccipdConstructorDeclarationNoSelfMacro( ClassName ) \
protected:                                                  \
  ClassName();                                              \
public:                                                     \
  virtual ~ClassName();
  
/**
* \brief Constructor/destructor empty definitions and declarations.
*/
#define ccipdConstructorEmptyDefinitionNoSelfMacro( ClassName ) \
protected:                                                  \
  ClassName() { }                                           \
public:                                                     \
  virtual ~ClassName() { }

/**
* \brief Constructor/destructor declarations and a Self typedef
*/
#define ccipdConstructorDeclarationMacro( ClassName ) \
  ccipdConstructorDeclarationNoSelfMacro( ClassName ) \
public:                                               \
  typedef ClassName Self;

/**
* \brief Constructor/destructor empty definitions and a Self typedef
*/
#define ccipdConstructorEmptyDefinitionsMacro( ClassName ) \
  ccipdConstructorEmptyDefinitionNoSelfMacro ( ClassName ) \
public:                                                    \
  typedef ClassName Self;
//////////////////////////////////////////////////////////////////////////////////////////

#define ccipdFactorylessNewMacro(xType)\
    static Pointer New(void)           \
        {                              \
            Pointer smartPtr;          \
            xType *rawPtr = new xType; \
            smartPtr = rawPtr;         \
            rawPtr->UnRegister();      \
            return smartPtr;           \
        }                                                          




//////////////////////////////////////////////////////////////////////////////////////////
/**
* \brief For classes extending Factory
* \note This assumes you have "Self" typedef'd!
* \note This assumes you extend Factory< Self >!
*/
#define ccipdFactorySuperclassMacro \
                                    \
public:                             \
  typedef Factory< Self > SuperclassFactory;

#define ccipdFactoryUsingMacro                          \
                                                        \
public:                                                 \
  using SuperclassFactory::New;                         \
  using SuperclassFactory::ConstNew;

/**
* This assumes you already have a typedef for SuperclassFactory
*/
#define ccipdFactoryTypedefsMacro                       \
                                                        \
public:                                                 \
  typedef SuperclassFactory::Pointer      Pointer;      \
  typedef SuperclassFactory::ConstPointer ConstPointer; \
                                                        \
  ccipdFactoryUsingMacro

#define ccipdFactoryTypedefsTemplatedMacro                       \
                                                                 \
public:                                                          \
  typedef typename SuperclassFactory::Pointer      Pointer;      \
  typedef typename SuperclassFactory::ConstPointer ConstPointer; \
                                                                 \
  ccipdFactoryUsingMacro


/**
* This is for classes which extend Factory directly
* and only requires "Self" typedef'd
*/
#define ccipdFactorySuperclassTypedefsMacro \
  ccipdFactorySuperclassMacro ccipdFactoryTypedefsMacro

#define ccipdFactorySuperclassTypedefsTemplatedMacro \
 ccipdFactorySuperclassMacro ccipdFactoryTypedefsTemplatedMacro

/**
* Implement the Factory and EnableSharedFromThis hxx.
* You must include Factory.hxx in the function this is called from
*/
#define ccipdFactoryImplementationMacro( ClassName ) \
  template class Factory < ClassName >; \
  template class EnableSharedFromThis < ClassName >; \
//////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////
/**
* PIMPL:
* http://en.wikipedia.org/wiki/Opaque_pointer
* http://herbsutter.com/gotw/_100/
* So others including this class don't see what type
* of data the class uses, and also don't
* need to include any custom itk .hxx files
* This goes into a header file.
*/
#define ccipdPIMPLMacro \
  private:                   \
  class SecretData;          \
  const std::unique_ptr< SecretData > m_SecretData;

/** Workaround for using PIMPl in ITK classes */
#define ccipdPIMPLMacroITK( ClassName ) \
  class SecretData;                          \
  struct SecretDataWorkaround :              \
    public std::unique_ptr< SecretData >     \
  {                                          \
    /* work around for using PIMPL in */     \
    /* itk classes http://bit.ly/JKm49d */   \
     SecretDataWorkaround();                 \
    ~SecretDataWorkaround();                 \
  } const m_SecretData;

/** Clearing the data */
#define ccipdClearDataMacro( ClassName )    \
  void ClassName::ClearData()               \
  {                                         \
    m_SecretData.reset( new SecretData() ); \
  }

#define ccipdNewPIMPLMacro m_SecretData( new SecretData() )

#ifndef THIS
#define THIS this->m_SecretData //  [6/3/2013 Ahmad]
#endif
//////////////////////////////////////////////////////////////////////////////////////////

// Ahmad Algohary 12/01/2014
// Setters and getters for Qt-based classes
#define Q_PROPERTY_WITH_ACCESSORS(type, name)    \
    private: type m_##name;                                      \
    public: Q_PROPERTY(type m_##name READ #name WRITE set##name) \
        type const& #name () const { return m_##name; }          \
        void set##name (type const &val) { m_##name = val; }


//////////////////////////////////////////////////////////////////////////////////////////
/**
* For implementing a "Set" function using the PIMPL idiom.
* The "Implement" macros go in a C++ file.
* The "Declare" macros go in a header file.
* Modeled after http://itk.org/Doxygen/html/itkMacro_8h_source.html
*/

// just internal helper macros
#define ccipdSetBodyMacro( VariableName )    \
  m_SecretData->m_##VariableName = variable; \

#define ccipdSetBodyHashMacro( VariableName ) \
  ccipdSetBodyMacro( VariableName )           \
  this->ClearHash();                          \

/* By Value */
#define ccipdSetByvalDeclareMacro( VariableName, VariableType ) \
  virtual void Set##VariableName( const VariableType value );   \

#define ccipdSetByvalImplementMacro(                               \
  ClassName, VariableName, VariableType )                          \
  void ClassName::Set##VariableName( const VariableType variable ) \
  {                                                                \
    ccipdSetBodyMacro( VariableName )                              \
  }

#define ccipdSetByvalImplementHashMacro(                           \
  ClassName, VariableName, VariableType )                          \
  void ClassName::Set##VariableName( const VariableType variable ) \
  {                                                                \
    ccipdSetBodyHashMacro( VariableName )                          \
  }

/* By Reference */
#define ccipdSetByrefDeclareMacro( VariableName, VariableType )     \
  virtual void Set##VariableName( const VariableType & reference );

#define ccipdSetByrefImplementMacro(                                 \
  ClassName, VariableName, VariableType )                            \
  void ClassName::Set##VariableName( const VariableType & variable ) \
  {                                                                  \
    ccipdSetBodyMacro( VariableName )                                \
  }

#define ccipdSetByrefImplementHashMacro(                             \
  ClassName, VariableName, VariableType )                            \
  void ClassName::Set##VariableName( const VariableType & variable ) \
  {                                                                  \
    ccipdSetBodyHashMacro( VariableName )                            \
  }                                                                  
//////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////
/**
* For implementing a "Get" function using the PIMPL idiom.
* The "Implement" macros go in a C++ file.
* The "Declare" macros go in a header file.
* Modeled after http://itk.org/Doxygen/html/itkMacro_8h_source.html
*/

// just an internal helper macro
#define ccipdGetBodyMacro( VariableName ) \
  {                                       \
  return m_SecretData->m_##VariableName;  \
  }                                      

/* Non-constant version */
#define ccipdGetDeclareMacro( VariableName, VariableType ) \
  virtual VariableType Get##VariableName();               

#define ccipdGetImplementMacro(               \
  ClassName, VariableName, VariableType )     \
  VariableType ClassName::Get##VariableName() \
  ccipdGetBodyMacro( VariableName )            

/* Constant version */
#define ccipdGetConstDeclareMacro( VariableName, VariableType ) \
  virtual VariableType Get##VariableName() const;              

#define ccipdGetConstImplementMacro(                 \
  ClassName, VariableName, VariableType )            \
  VariableType ClassName::Get##VariableName() const  \
  ccipdGetBodyMacro( VariableName )                  
//////////////////////////////////////////////////////////////////////////////////////////
#define ccipdLoadSaveDeclareMacro   \
                                    \
  /** Load from an XML file */      \
  virtual bool Load(                \
    const std::string & fileName ); \
                                    \
  /** Save to an XML file */        \
  virtual bool Save(                \
    const std::string & fileName ) const;

#define ccipdLoadSaveImplementationMacro( ClassName )  \
  bool ClassName::Load( const std::string & fileName ) \
  {                                                    \
    bool loaded = false;                               \
    ccipdLoadImplementationBodyMacro                   \
    return loaded;                                     \
  }                                                    \
                                                       \
  bool ClassName::Save( const std::string & fileName ) \
  const                                                \
  {                                                    \
    bool saved = false;                                \
    ccipdSaveImplementationBodyMacro                   \
    return saved;                                      \
  }                                                    

//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////

/*
	msg: message when exception is unknown
	ret: what to return when exception is caught
	Author: Ahmad
*/
#define ccipdCatchExceptionMacro(msg, ret)                          \
  catch( itk::ExceptionObject &err )                                \
    {                                                               \
    std::cerr << err << "Code: " << __FILE__                        \
    << ":"<< __LINE__ << std::endl;                                 \
    return ret;                                                     \
    }                                                               \
  catch ( ... )                                                     \
    {                                                               \
     std::cerr << msg << "\" ... \n" << "Unknown Exception caught." \
     << "\n" << __FILE__ << ":"<< __LINE__ << std::endl;            \
     return ret;                                                    \
    }



/** Set built-in type.  Creates member Set"name"() (e.g., SetVisibility()); */
#define ccSetMacro(name, type)                     \
  virtual void Set##name (const type _arg)         \
    {                                              \
        if ( this->m_##name != _arg )              \
        {                                          \
          this->m_##name = _arg;                   \
          this->Modified();                        \
        }                                          \
    }

/** Get built-in type.  Creates member Get"name"() (e.g., GetVisibility()); */
#define ccGetMacro(name, type)   \
  virtual type Get##name ()      \
    {                            \
        return this->m_##name;   \
    }

/** Set pointer to object; uses Object reference counting methodology.
 * Creates method Set"name"() (e.g., SetPoints()). Note that using
 * smart pointers requires using real pointers when setting input,
 * but returning smart pointers on output. */
#define ccSetObjectMacro(name, type)                  \
  virtual void Set##name (type * _arg)                \
    {                                                 \
        if ( this->m_##name != _arg )                 \
        {                                             \
          this->m_##name = _arg;                      \
          this->Modified();                           \
        }                                             \
    }

#  define ccGetObjectMacro(name, type)       \
  virtual type * GetModifiable##name ()      \
  {                                          \
    return this->m_##name.GetPointer();      \
  }    
#endif // __ccipdMacros_h
