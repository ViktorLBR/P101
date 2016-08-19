#include "stdafx.h"

using namespace std;

#ifndef OGLI_SLOT
#define OGLI_SLOT

#include "Input.h"

namespace ogli
{
	class primitif_TicInput : public sblCElement
	{
	public:
		virtual void tic(Input & input)
		{

		}
	};

	class primitif_Slot : public primitif_TicInput
	{
	public:
		virtual void actualiser()
		{

		}
	};

	class b_BSlot : public primitif_Slot
	{
	public:
		b_BSlot()
		{
			value = false;
		}
		~b_BSlot()
		{
			value = false;
		}

		virtual void inTrue()
		{
			sblCElement::execFonction("inTrue");
		}
		virtual void inFalse()
		{
			sblCElement::execFonction("inFalse");
		}

		virtual void setValue(bool val)
		{
			value = val;
		}
		virtual bool getValue()
		{
			return value;
		}

		virtual void actualiser()
		{
			if (value == true)
				inTrue();
			else
				inFalse();
		}

		virtual int set(string nvar, lua_State * L)
		{
			if (nvar == "value")
			{
				setValue(lua_toboolean(L, 2));
				return 0;
			}

			return sblCElement::set(nvar, L);
		}
		virtual int get(string nvar, lua_State * L)
		{
			if (nvar == "value")
			{
				lua_pushboolean(L, getValue());
				return 1;
			}

			return sblCElement::set(nvar, L);

		}
		virtual int exec(string nfonc, lua_State * L)
		{
			if (nfonc == "actualiser")
			{
				actualiser();
				return 0;
			}

			return sblCElement::exec(nfonc, L);
		}
		virtual sblElement * Copie()
		{
			b_BSlot * p = new b_BSlot();
			HCopie(p);
			return p;
		}

	protected:
		bool value;

		virtual void HCopie(b_BSlot * p)
		{
			p->map_fonctions = map_fonctions;
			p->value = value;
			sblCElement::HCopie(p);
		}
	};

	class b_Slot : public b_BSlot
	{
	public:

		b_Slot()
		{
			hvalue = value = false;
		}

		virtual void inChange()
		{
			sblCElement::execFonction("inStable");
		}
		virtual void inStable()
		{
			sblCElement::execFonction("inStable");
		}

		virtual void actualiser()
		{
			if (value == true)
				inTrue();
			else
				inFalse();
			if (hvalue == value)
				inStable();
			else
				inChange();
			hvalue = value;
		}

		virtual sblElement * Copie()
		{
			b_Slot * p = new b_Slot();
			HCopie(p);
			return p;
		}

	protected:
		bool hvalue;

		virtual void HCopie(b_Slot * p)
		{
			p->hvalue = hvalue;
			b_BSlot::HCopie(p);
		}
	};

	class hub_Slot : public gen::Executeur<primitif_Slot>
	{
	public:

		hub_Slot()
		{
			nom = "hub_Slot";
		}

		virtual void operation(primitif_Slot * p)
		{
			p->actualiser();
		}
	};

	class hub_TicInput : public gen::Executeur<primitif_TicInput>
	{
	public:
		Input & input;

		hub_TicInput(Input & input) : input(input)
		{
			nom = "hub_TicInput";
		}

		virtual void operation(primitif_TicInput * p)
		{
			p->tic(input);
		}
	};
};


#endif