/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:04:29 by nwyseur           #+#    #+#             */
/*   Updated: 2023/09/29 16:49:39 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stack>
# include <exception>
# include <cstdlib>

class RPN
{
	public:
		RPN(char* IPE);
		~RPN() {}

		void parsing(void);
		void calculation(void);
		void operation(char c);
		void plus(void);
		void moins(void);
		void diviser(void);
		void fois(void);
		
		class invalidFormatException : public std::exception
		{
			public:
				invalidFormatException(const std::string& msg)
				{
					_message = msg;
				}
				virtual const char* what() const throw()
				{
					return (_message.c_str());
				}
				virtual ~invalidFormatException() throw() {}

			private:
				std::string _message;
		};

	private:
		RPN();
		RPN(RPN const& other);
		RPN& operator=(RPN const& other);
		std::string _IPE;
		std::stack<int> _pile;

};


#endif