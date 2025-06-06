# C++ 커리큘럼 전체 구조 및 예제 코드 트리

## 📚 커리큘럼 구조 (8 Chapters)

### Chapter 01: C++ 기초와 개발환경
- C++ 언어 특징과 C와의 차이점
- 개발환경 설치 및 설정  
- 이름공간(namespace) 개념과 활용
- 표준 입출력(cin, cout) 기초 실습

### Chapter 02: 변수, 데이터 타입과 메모리 관리
- 기본 데이터 타입과 변수 선언
- 레퍼런스(reference) 개념과 활용
- 포인터 기초와 동적 메모리 할당(new/delete)
- 스마트 포인터 소개(unique_ptr, shared_ptr)

### Chapter 03: 함수와 배열
- 함수 선언과 정의, 매개변수 전달 방식
- 함수 오버로딩과 디폴트 매개변수
- 배열과 문자열 처리
- 표준 라이브러리 string과 배열 활용

### Chapter 04: 클래스와 객체지향 I
- 구조체와 클래스 비교
- 클래스 멤버와 접근 제어
- 생성자와 소멸자
- 복사/이동 생성자와 연산자 오버로딩 기초

### Chapter 05: 클래스와 객체지향 II
- 정적(static) 멤버와 const 멤버
- 연산자 오버로딩 심화
- 프렌드(friend) 함수와 클래스
- 현대 C++의 객체 관리(이동 의미론)

### Chapter 06: 상속과 다형성
- 상속 개념과 접근 지정자
- 가상 함수와 오버라이딩
- 순수 가상 함수와 추상 클래스
- 객체 포인터와 다형성 활용

### Chapter 07: 템플릿과 STL
- 함수 템플릿과 클래스 템플릿
- STL 컨테이너 소개(vector, list, map)
- 반복자(iterator)와 알고리즘 기초
- 람다 표현식과 STL 알고리즘 활용

### Chapter 08: 예외 처리와 프로젝트
- 예외 처리 기본 개념과 try-catch 구문
- 예외 안전성과 RAII 패턴
- 실전 코딩 예제 분석 및 실습
- C++ 개발 모범 사례와 추가 학습 방향

---

## 🗂️ 예제 코드 트리 구조

```
C++_Curriculum_Examples/
├── Chapter01_기초와개발환경/
│   ├── 01_hello_world.cpp
│   ├── 02_namespace_basic.cpp
│   ├── 03_namespace_std.cpp
│   ├── 04_input_output_basic.cpp
│   ├── 05_multiple_output.cpp
│   ├── 06_user_input.cpp
│   ├── 07_formatted_output.cpp
│   ├── 08_comments_usage.cpp
│   ├── 09_compilation_process.cpp
│   └── 10_debugging_basics.cpp
│
├── Chapter02_변수와데이터타입/
│   ├── 01_basic_datatypes.cpp
│   ├── 02_variable_declaration.cpp
│   ├── 03_reference_basic.cpp
│   ├── 04_reference_vs_pointer.cpp
│   ├── 05_pointer_basic.cpp
│   ├── 06_dynamic_memory.cpp
│   ├── 07_memory_leak_example.cpp
│   ├── 08_smart_pointer_unique.cpp
│   ├── 09_smart_pointer_shared.cpp
│   └── 10_memory_management_best.cpp
│
├── Chapter03_함수와배열/
│   ├── 01_function_basic.cpp
│   ├── 02_parameter_passing.cpp
│   ├── 03_function_overloading.cpp
│   ├── 04_default_parameters.cpp
│   ├── 05_array_basic.cpp
│   ├── 06_array_functions.cpp
│   ├── 07_string_processing.cpp
│   ├── 08_std_string.cpp
│   ├── 09_multidimensional_array.cpp
│   └── 10_array_algorithms.cpp
│
├── Chapter04_클래스와객체지향1/
│   ├── 01_struct_vs_class.cpp
│   ├── 02_class_members.cpp
│   ├── 03_access_control.cpp
│   ├── 04_constructor_basic.cpp
│   ├── 05_destructor_basic.cpp
│   ├── 06_constructor_overloading.cpp
│   ├── 07_copy_constructor.cpp
│   ├── 08_assignment_operator.cpp
│   ├── 09_move_constructor.cpp
│   └── 10_object_lifecycle.cpp
│
├── Chapter05_클래스와객체지향2/
│   ├── 01_static_members.cpp
│   ├── 02_const_members.cpp
│   ├── 03_operator_overloading_basic.cpp
│   ├── 04_operator_overloading_advanced.cpp
│   ├── 05_friend_function.cpp
│   ├── 06_friend_class.cpp
│   ├── 07_move_semantics.cpp
│   ├── 08_perfect_forwarding.cpp
│   ├── 09_rvalue_reference.cpp
│   └── 10_modern_cpp_features.cpp
│
├── Chapter06_상속과다형성/
│   ├── 01_inheritance_basic.cpp
│   ├── 02_access_specifiers.cpp
│   ├── 03_constructor_inheritance.cpp
│   ├── 04_virtual_function.cpp
│   ├── 05_function_overriding.cpp
│   ├── 06_pure_virtual_function.cpp
│   ├── 07_abstract_class.cpp
│   ├── 08_polymorphism_basic.cpp
│   ├── 09_virtual_destructor.cpp
│   └── 10_multiple_inheritance.cpp
│
├── Chapter07_템플릿과STL/
│   ├── 01_function_template.cpp
│   ├── 02_class_template.cpp
│   ├── 03_template_specialization.cpp
│   ├── 04_stl_vector.cpp
│   ├── 05_stl_list.cpp
│   ├── 06_stl_map.cpp
│   ├── 07_iterators.cpp
│   ├── 08_algorithms.cpp
│   ├── 09_lambda_expressions.cpp
│   └── 10_stl_advanced.cpp
│
├── Chapter08_예외처리와프로젝트/
│   ├── 01_exception_basic.cpp
│   ├── 02_try_catch.cpp
│   ├── 03_custom_exceptions.cpp
│   ├── 04_exception_safety.cpp
│   ├── 05_raii_pattern.cpp
│   ├── 06_resource_management.cpp
│   ├── 07_project_structure.cpp
│   ├── 08_coding_standards.cpp
│   ├── 09_debugging_techniques.cpp
│   └── 10_final_project.cpp
│
├── Common/
│   ├── utils.h
│   ├── common_defines.h
│   └── test_framework.h
│
├── Projects/
│   ├── Mini_Calculator/
│   ├── Student_Management/
│   ├── Bank_Account_System/
│   └── Game_Character_System/
│
└── README.md
```

## 📋 각 챕터별 예제 개요

### Chapter 01 (10개 예제)
1. **Hello World** - 기본 출력
2. **Namespace Basic** - 네임스페이스 정의와 사용
3. **Namespace STD** - std 네임스페이스 활용
4. **Input/Output Basic** - cin/cout 기본 사용법
5. **Multiple Output** - 여러 데이터 출력
6. **User Input** - 사용자 입력 처리
7. **Formatted Output** - 서식 있는 출력
8. **Comments Usage** - 주석 활용법
9. **Compilation Process** - 컴파일 과정 이해
10. **Debugging Basics** - 기본 디버깅

### Chapter 02 (10개 예제)
1. **Basic Datatypes** - 기본 데이터 타입
2. **Variable Declaration** - 변수 선언과 초기화
3. **Reference Basic** - 레퍼런스 기본 개념
4. **Reference vs Pointer** - 레퍼런스와 포인터 비교
5. **Pointer Basic** - 포인터 기본 사용법
6. **Dynamic Memory** - 동적 메모리 할당
7. **Memory Leak Example** - 메모리 누수 예제
8. **Smart Pointer Unique** - unique_ptr 사용법
9. **Smart Pointer Shared** - shared_ptr 사용법
10. **Memory Management Best** - 메모리 관리 모범 사례

### Chapter 03-08 (각각 10개씩)
*[동일한 방식으로 각 챕터별 10개씩 상세 예제 구성]*

---

## 🎯 수업자료 스타일 가이드

### 작성 원칙
- **간단명료하면서 정확한 설명**
- **실무적이고 현실적인 예제**
- **단계별 점진적 학습**
- **현대 C++ 기법 반영**

### 코드 스타일
- 읽기 쉬운 변수명 사용
- 적절한 주석 포함
- 실행 가능한 완전한 예제
- 에러 처리 포함

### 설명 구조
1. **개념 설명** (Why & What)
2. **기본 문법** (How)
3. **실용적 예제** (Practice)
4. **주의사항 및 팁** (Tips)
5. **실습 과제** (Exercise)

---

**준비 완료!** "다음"이라고 말씀해주시면 원하시는 챕터부터 상세한 수업자료를 작성해드리겠습니다.
