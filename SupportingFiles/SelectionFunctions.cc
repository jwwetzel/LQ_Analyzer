#include "SelectionFunctions.h"

/***************************************************************************************
* 
* Function: isGoodEvent_v1
* 
****************************************************************************************/
Bool_t isGoodEvent(Int_t nVertex, std::vector<Double_t> Vertex_Ndof, std::vector<Double_t> Vertex_X,  std::vector<Double_t> Vertex_Y, std::vector<Double_t> Vertex_Z, Double_t beamspot_x, Double_t beamspot_y, Bool_t *goodVerticies)
{
  if (nVertex>0)
  {
    if (nVertex>50)
    {
      //cout<<"nVertex "<<nVertex<<endl;
      nVertex=50;
    }
    for (Int_t i=0; i<nVertex; i++)
    {
      if ( Vertex_Ndof[i]>4 && fabs(Vertex_Z[i])<=24 && fabs(sqrt(pow(Vertex_X[i],2)+pow(Vertex_Y[i],2))-sqrt(pow(beamspot_x,2)+pow(beamspot_y,2)))<=2 )
      {
         goodVerticies[i] = true;
         return true;
      }
      else
      {
         goodVerticies[i] = false;
      }
    }
    return false;
  }
  else
  {
    return false;
  }
}

/***************************************************************************************
*
* Function: isGoodEvent_v2
*
****************************************************************************************/
Bool_t isGoodEvent(Int_t nVertex, std::vector<Bool_t> Vertex_Fake, std::vector<Double_t> Vertex_Ndof, std::vector<Double_t> Vertex_X,  std::vector<Double_t> Vertex_Y, std::vector<Double_t> Vertex_Z, Bool_t *goodVerticies)
{
  if (nVertex>0)
  {
    for (Int_t i=0; i<nVertex; i++)
    {
      if ( Vertex_Ndof[i]>4 && fabs(Vertex_Z[i])<=24 
          && sqrt(pow(Vertex_X[i],2)+pow(Vertex_Y[i],2))<=2
          && !Vertex_Fake[i]
          )
      {
        goodVerticies[i] = true;
        return true;
      }
      else
      {
        goodVerticies[i] = false;
      }
    }
    return false;
  }
  else
  {
    return false;
  }
}

/***************************************************************************************
*
* Function: Zselection
*
****************************************************************************************/
Bool_t Zselection(std::vector<Lepton>& leptonColl, Double_t MET)
{
  Double_t mass=0;
  Double_t temp_mass=0;
  if (leptonColl.size()==2)
  {
    for (UInt_t i=0; i<leptonColl.size()-1; i++)
    {
      for(UInt_t j=i+1; j<leptonColl.size(); j++)
      {
        if (leptonColl[i].charge() != leptonColl[j].charge())
        {
          temp_mass = (leptonColl[i].lorentzVec() + leptonColl[j].lorentzVec()).M();
          if (fabs(temp_mass-Mass_Z) < fabs(mass-Mass_Z)) mass = temp_mass;
        }
      }
    }
    if (MET < 20 && mass > (Mass_Z-20) && mass < (Mass_Z+20))
      return true;
    else
      return false;
  }
  else
    return false;
}

/***************************************************************************************
*
* Function: ZVeto
*
* A third muon could be reconstructed from a number of sources.
* One clear source is the decay of a Z boson to two muons.
* This function checks to see if any two muons are reconstructed
* to a mass within 15 GeV of the Z Boson, (roughly 1 sigma of Z Boson mass).
*
* Returns 'True' if combined muon mass is greater than +/-15 GeV of Z Mass.
*
****************************************************************************************/
//bool ZVeto(std::vector<Lepton>& leps)
//{
//   Double_t mass3rd=999.9;
//   double massZ = 91.1876;
//   if(leps.size() > 2)
//   {
//     for(UInt_t i=0; i<leps.size()-1; i++)
//     {
//       for(UInt_t j=i+1; j<leps.size(); j++)
//       {
//          if ( leps[i].charge() != leps[j].charge() )
//          {
//             float tempmass3rd = (leps[i].lorentzVec() + leps[j].lorentzVec()).M();	    
//             if (fabs(mass3rd-massZ) > fabs(tempmass3rd-massZ)) mass3rd = tempmass3rd;
//          }
//       }
//     }
//   }
//   return (fabs(mass3rd-massZ) > 15);
//}

/***************************************************************************************
*
* Function: LowMassVeto
*
***************************************************************************************/
bool LowMassVeto(std::vector<Lepton>& leps)
{
    Double_t masslow=999.9;
    if(leps.size() >= 2)
    {
      masslow = (leps[0].lorentzVec() + leps[1].lorentzVec()).M();
    }
    return (masslow>=10);
}

/***************************************************************************************
 *
 * Function: ZVeto
 *
 * This simply requires only two muons, and returns false
 *
 ***************************************************************************************/
bool ZVeto(std::vector<Lepton>& leps)
{
   return (leps.size() - looseMuonDeltaRVeto(leps) <= 2);
}

/***************************************************************************************
*
* Function:  muonDeltaRVeto
*
* Sorts through a collection of 'loose' muons and vetos the event if more than two 
* 'loose' muons exists, while ensuring there are no split tracks.
*
* For loose collections, split tracks can lead to double counting of muons.
*
* Loose muons are defined in the following link:
* https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId#Loose_Muon
*
* These selection rules are implemented in Analyzer.cc, and here we add another rule,
* that the delta R between two muons be at least 0.2cm.
* 
* Returns True if number of muons - number of pairs is <= 2, and false if 3 or more muons
* are in the event.
* 
***************************************************************************************/
bool looseMuonDeltaRVeto(std::vector<Lepton>& leps)
{
   Float_t muDeltaR = 999.9;
   int nDeltaR = 0;
   if (leps.size() >= 2)
   {
      for (UInt_t i=0; i<leps.size()-1; ++i)
      {
         for (UInt_t j=i+1; j<leps.size(); ++j)
         {
            muDeltaR = leps[i].lorentzVec().DeltaR(leps[j].lorentzVec());            
            if (muDeltaR > 0.2 ) ++nDeltaR;
         }
      }
   }
   return (nDeltaR < 2);
}

/***************************************************************************************
*
* Function: PileUpDeposit
*
****************************************************************************************/
double PileUpDeposit(double _rho, double _eta, bool hcal)
{
  _eta = fabs(_eta);
  if(hcal)
  {
   //if (_eta < 1.479) return _rho*0.022;
   //else return _rho*0.030;
    if (_eta < 0.5) return _rho*0.029;
    else if (_eta < 1.0) return _rho*0.027;
    else if (_eta < 1.5) return _rho*0.036;
    else if (_eta < 2.0) return _rho*0.040;
    else return _rho*0.054;
  }
  else
  {
   //if(_eta < 1.479) return _rho*0.074;
   //else return _rho*0.045;
    if (_eta < 0.5) return _rho*0.091;
    else if (_eta < 1.0) return _rho*0.077;
    else if (_eta < 1.5) return _rho*0.055;
    else if (_eta < 2.0) return _rho*0.034;
    else return _rho*0.046;
  }
}

/***************************************************************************************
*
* Function: PileUpDeposit2Eta
*
****************************************************************************************/
double PileUpDeposit2Eta(double _rho, double _eta, bool hcal)
{
   if(hcal)
   {
      //if (_eta < 1.479) return _rho*0.022;
      //else return _rho*0.030;
      if (_eta < 1.479) return _rho*0.046;
      else return _rho*0.040;
   }
   else
   {
      //if(_eta < 1.479) return _rho*0.074;
      //else return _rho*0.045;
      if (_eta < 1.479) return _rho*0.101;
      else return _rho*0.046;
   }
}

/***************************************************************************************
*
* Function: ZandWveto
*
****************************************************************************************/
Bool_t ZandWveto(std::vector<Lepton>& leptonColl, Double_t MET, Double_t METPhi)
{
  Double_t mass=0;
  Double_t temp_mass=0;
  Double_t temp_MT=0;
  Double_t MT=0;
  for(UInt_t w=0; w<leptonColl.size(); w++)
  {
    temp_MT = sqrt(2.*leptonColl[w].lorentzVec().Et()*MET* (1 - cos(leptonColl[w].lorentzVec().Phi()-METPhi)) );
    if ( temp_MT > MT) 
      MT = temp_MT;
  }
  if (leptonColl.size()>=2)
  {
    for (UInt_t i=0; i<leptonColl.size()-1; i++)
      for(UInt_t j=i+1; j<leptonColl.size(); j++)
      {
         if ( leptonColl[i].charge() != leptonColl[j].charge() && leptonColl[i].lorentzVec().Pt()>20 && leptonColl[j].lorentzVec().Pt()>20)
         {
           temp_mass = (leptonColl[i].lorentzVec() + leptonColl[j].lorentzVec()).M();
           if (fabs(temp_mass-Mass_Z) < fabs(mass-Mass_Z)) mass=temp_mass;
         }
      }
  } 
  if (MET < 20 && MT < 20 && (mass < (Mass_Z-20) || mass > (Mass_Z+20) ))
    return false;
  else
    return true;
}

/***************************************************************************************
*
* Function: TriggerSelector
*
****************************************************************************************/
Bool_t TriggerSelector (std::vector<TString> triggernames, std::vector<string> inputtriggers, std::vector<Bool_t> triggerdecision)
{
  for (UInt_t i=0; i<inputtriggers.size(); i++)
  {
    if (triggerdecision[i])
    {
      TString tmpHLT = inputtriggers[i];
      for (std::vector<TString>::iterator it=triggernames.begin(); it !=  triggernames.end(); ++it)
      {
         if (tmpHLT.BeginsWith(*it)) return true;
      }
    }
  }
  return false;
}
