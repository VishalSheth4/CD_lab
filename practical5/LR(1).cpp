/*
�ķ����ڡ�wenfa.txt���У�FIRST���š�first.txt����

�ķ���Ϊ�����ķ���ÿ��һ������ʽ���������á�#�����棬���ս���ô�д��ĸ���ս����Сд��ĸ

FIRST����ʽΪ�����ս�� �ս�������ַ�����ÿ��һ�����硰E (i�������á�%������

����ACTION����action.txt�У�GOTO����goto.txt��
*/
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<cctype>
#include<algorithm>
#include<set>
#include<map>
#include<deque>
using namespace std;
class a_xiang
{
public:
 a_xiang::a_xiang(){}
 a_xiang::a_xiang(const string& str,set<char>& forw):a_shizi(str),forword(forw){}
 string& geta_shizi(){return a_shizi;}
 set<char>& getforword(){return forword;}
 void push_forword(set<char>& sv){forword.insert(sv.begin(),sv.end());}
 friend bool operator==(const a_xiang& lhs,const a_xiang& rhs);
private:
 string a_shizi;
 set<char> forword;
};
class xiangji
{
public:
 void closure();
 void push_a_xiang(const a_xiang orig){xiang.push_back(orig);}
 void output();
 vector<a_xiang>& get_xiang(){return xiang;}
 set<pair<char,int> >& get_action(){return action;}
 friend bool operator==(const xiangji& lhs,const xiangji& rhs);
private:
 vector<a_xiang> xiang;
 set<pair<char,int> > action;
};

map<char,set<char> > first;
vector<string> wenfa,wenfa_dian;
deque<xiangji> gototu;
set<char> zhongjiefu,feizhongjiefu;
vector<vector<int> >actions,gotos;
bool operator==(const a_xiang& lhs,const a_xiang& rhs)
{
 if(lhs.a_shizi!=rhs.a_shizi) return false;
 if(lhs.forword.size()!=rhs.forword.size()) return false;
 set<char>::const_iterator lhs_it=lhs.forword.begin(),rhs_it=rhs.forword.begin();
 while(lhs_it!=lhs.forword.end())
 {
  if(*lhs_it!=*rhs_it) return false;
  ++lhs_it;
  ++rhs_it;
 }
 return true;
}
bool operator==(const xiangji& lhs,const xiangji& rhs)
{
 if(lhs.xiang.size()==rhs.xiang.size())
 {
  for(vector<a_xiang>::const_iterator lhs_it=lhs.xiang.begin();lhs_it!=lhs.xiang.end();++lhs_it)
  {
   vector<a_xiang>::const_iterator rhs_it=rhs.xiang.begin();
   for(;rhs_it!=rhs.xiang.end();++rhs_it)
    if(*lhs_it==*rhs_it) break;
   if(rhs_it==rhs.xiang.end()) return false;
  }
  return true;
 }
 else return false;
}
void changewenfa()
{
 vector<string>::iterator it=wenfa.begin();
 while(it!=wenfa.end())
 {
  string a_line(*it);
  if(a_line.size()==2) a_line.push_back('!');
  else
  {
   string::iterator p=a_line.begin();
   ++p;++p;
   a_line.insert(p,'!');
  }
  wenfa_dian.push_back(a_line);
  ++it;
 }
}
void inputwenfa(const string& wenfa_file)//�����ķ��ļ�
{
 ifstream in;
 in.open(wenfa_file.c_str());
 string a_line;
 while(getline(in,a_line))
  wenfa.push_back(a_line);
 in.close();
 changewenfa();
}

void inputfirst(const string& first_file)//����FIRST�ļ�
{
 ifstream in;
 in.open(first_file.c_str());
 string a_line;
 while(getline(in,a_line))
 {
  char ch=a_line[0];
  for(int i=2;i!=a_line.size();++i)
   first[ch].insert(a_line[i]);
 }
 in.close();
}

bool isfeizhongjiefu(char c)
{
 if(c>='A'&&c<='Z') return true;
 else return false;
}
bool iszhongjiefu(char c)
{
 return !isfeizhongjiefu(c);
}
vector<string> chanshengshi(char c)
{
 vector<string> vec;
 for(vector<string>::iterator it=wenfa_dian.begin();it!=wenfa_dian.end();++it)
  if((*it)[0]==c) vec.push_back(*it);
 return vec;
}
set<char> findfirst(const string& str,set<char>& forword)
{
 if(str=="") return forword;
 else if(iszhongjiefu(str[0]))
 {
  set<char> setc;
  setc.insert(str[0]);
  return setc;
 }
 else// if(isfeizhongjiefu(str[0]))
 {
  set<char> setc;
  string::const_iterator p=str.begin();
  while(p!=str.end())
  {
   setc.insert((first[*p]).begin(),(first[*p]).end());
   if((first[*p]).find('%')!=first[*p].end()) ++p;
   else break;
  }
  if(p==str.end()) setc.insert(forword.begin(),forword.end());
  setc.erase('%');
  return setc;
 }
}

 

void xiangji::closure()
{
 for(vector<a_xiang>::size_type it=0;it!=xiang.size();++it)
 {
  for(string::iterator p=xiang[it].geta_shizi().begin();p!=xiang[it].geta_shizi().end();++p)
  {
   if(*p=='!')
   {
    if((++p)!=xiang[it].geta_shizi().end()&&isfeizhongjiefu(*p))
    {
     string hou(++p,xiang[it].geta_shizi().end());
     
     set<char> forword_2(findfirst(hou,xiang[it].getforword()));
     vector<string> shi(chanshengshi(*(--p)));
     for(vector<string>::iterator jp=shi.begin();jp!=shi.end();++jp)
     {
      vector<a_xiang>::iterator xiang_it=xiang.begin();
      while(xiang_it!=xiang.end())
      {
       if((*jp)==xiang_it->geta_shizi())
       {
        xiang_it->push_forword(forword_2);
        break;
       }
       ++xiang_it;
      }
      if(xiang_it==xiang.end())
       xiang.push_back(a_xiang((*jp),forword_2));
     }
     break;
    }
    --p;
   }
  }
  
 }
}


void xiangji::output()
{
 vector<a_xiang>::iterator ip=xiang.begin();
 while(ip!=xiang.end())
 {
  cout<<(*ip).geta_shizi()<<'\t';
  set<char>::iterator iit=ip->getforword().begin();
  while(iit!=ip->getforword().end())
  {
   cout<<*iit<<" ";
   ++iit;
  }
  cout<<endl;
  ++ip;
 }
}
xiangji go_to(xiangji& orig,char x)
{
 xiangji xia_j;
 for(vector<a_xiang>::iterator it=orig.get_xiang().begin();it!=orig.get_xiang().end();++it)
 {
  string shizi(it->geta_shizi());
  string::iterator p=find(shizi.begin(),shizi.end(),'!');
  if(++p!=shizi.end()&&(*p)==x)
  {
   p=shizi.erase(p);
   --p;
   shizi.insert(p,x);
   xia_j.get_xiang().push_back(a_xiang(shizi,it->getforword()));
  }
 }
 xia_j.closure();
 return xia_j;
}
bool isdifferent(xiangji& orig)
{
 bool flag=true;
 for(vector<xiangji>::size_type i=0;i!=gototu.size();++i)
 {
  if(orig==gototu[i])
  {
   flag=false;
   break;
  }
 }
 return flag;
}

void items()
{
 xiangji start;
 set<char> start_forword;
 start_forword.insert('$');
 start.push_a_xiang(a_xiang(wenfa_dian.front(),start_forword));
 start.closure();
 gototu.push_back(start);
 for(vector<xiangji>::size_type i=0;i!=gototu.size();++i)
 {
  for(vector<a_xiang>::iterator p=gototu[i].get_xiang().begin();p!=gototu[i].get_xiang().end();++p)
  {
   string::iterator it=find(p->geta_shizi().begin(),p->geta_shizi().end(),'!');
   ++it;
   if(it==p->geta_shizi().end()) continue;
   xiangji a_new_xiangji(go_to(gototu[i],*it));
   if(isdifferent(a_new_xiangji))
   {
    gototu[i].get_action().insert(make_pair(*it,gototu.size()));
    gototu.push_back(a_new_xiangji);
   }
   else
   {
    for(vector<xiangji>::size_type ip=0;ip!=gototu.size();++ip)
    {
     if(a_new_xiangji==gototu[ip])
      gototu[i].get_action().insert(make_pair(*it,ip));
    }
   }
  }
 }
}
void findzhongjiefu()
{
 for(vector<string>::iterator it=wenfa.begin();it!=wenfa.end();++it)
 {
  for(string::iterator p=it->begin();p!=it->end();++p)
  {
   if(isupper(*p)) feizhongjiefu.insert(*p);
   else if(*p!='#') zhongjiefu.insert(*p);
  }
 }
 zhongjiefu.insert('$');
 feizhongjiefu.erase(wenfa[0][0]);
}
void creat_goto()
{
 for(deque<xiangji>::iterator it=gototu.begin();it!=gototu.end();++it)
 {
  vector<int> line_goto;
  for(set<char>::iterator zhong_it=feizhongjiefu.begin();zhong_it!=feizhongjiefu.end();++zhong_it)
  {
   set<pair<char,int> >::iterator p=it->get_action().begin();
   for(;p!=it->get_action().end();++p)
   {
    if(*zhong_it==p->first)
    {
     line_goto.push_back(p->second);
     break;
    }
   }
   if(p==it->get_action().end()) line_goto.push_back(0);
  }
  gotos.push_back(line_goto);
 }
}
void creat_action()
{
 for(deque<xiangji>::iterator it=gototu.begin();it!=gototu.end();++it)
 {
  vector<int> line_action;
  for(set<char>::iterator zhong_it=zhongjiefu.begin();zhong_it!=zhongjiefu.end();++zhong_it)
  {
   set<pair<char,int> >::iterator p=it->get_action().begin();
   for(;p!=it->get_action().end();++p)
   {
    if(*zhong_it==p->first)
    {
     line_action.push_back(p->second);
     break;
    }
   }
   if(p==it->get_action().end()) line_action.push_back(0);
  }
  for(vector<a_xiang>::iterator it_shi=it->get_xiang().begin();it_shi!=it->get_xiang().end();++it_shi)
  {
   string str(it_shi->geta_shizi());
   if(str[str.size()-1]=='!')
   {
    string::iterator ip_str=str.end();
    --ip_str;
    str.erase(ip_str);
    int num_shi=0;
    for(;num_shi!=wenfa.size();++num_shi)
    {
     if(str==wenfa[num_shi]) break;
    }
    for(set<char>::iterator set_it=it_shi->getforword().begin();set_it!=it_shi->getforword().end();++set_it)
    {
     int num=0;
     for(set<char>::iterator it_zhong=zhongjiefu.begin();it_zhong!=zhongjiefu.end();++it_zhong)
     { 
      if(*set_it==*it_zhong) break;
      ++num;
     }
     if(str[0]==wenfa[0][0]) line_action[num]=999;
     else line_action[num]=-num_shi;
    }
   }
  }
  actions.push_back(line_action);
 }
}
void output_fenxibiao()
{
 ofstream out_action("action.txt"),out_goto("goto.txt");
 cout<<endl;
 cout<<"LR(1)��������"<<endl;
 cout<<endl<<'\t';
 set<char>::iterator zhong_it=zhongjiefu.begin();
 while(zhong_it!=zhongjiefu.end())
 {
  cout<<*zhong_it++<<'\t';
 }
 set<char>::iterator feizhong_it=feizhongjiefu.begin();
 while(feizhong_it!=feizhongjiefu.end())
 {
  cout<<*feizhong_it++<<'\t';
 }
 cout<<endl;
 int line=0;
 for(vector<vector<int> >::iterator i_1=actions.begin(),i_3=gotos.begin();i_1!=actions.end();++i_1,++i_3,++line)
 {
  cout<<line<<'\t';
  for(vector<int>::iterator i_2=i_1->begin();i_2!=i_1->end();++i_2)
  {
   cout<<*i_2<<'\t';
   out_action<<*i_2<<',';
  }
  for(vector<int>::iterator i_4=i_3->begin();i_4!=i_3->end();++i_4)
  {
   cout<<*i_4<<'\t';
   out_goto<<*i_4<<',';
  }
  cout<<endl;
  out_action<<endl;
  out_goto<<endl;
 }

}
void output_zhuangtaitu()
{
 cout<<"��"<<gototu.size()<<"��״̬"<<endl<<endl;
 for(deque<xiangji>::size_type itp=0;itp!=gototu.size();++itp)
 {
  cout<<"״̬:"<<itp<<endl;
  gototu[itp].output();
  for(set<pair<char,int> >::iterator iiip=gototu[itp].get_action().begin();iiip!=gototu[itp].get_action().end();++iiip)
  {
   cout<<"���룺"<<iiip->first<<"\t"<<"��ת����"<<iiip->second<<endl;
  }
  cout<<endl;
 }
}
void output_zhongjiefu()
{
 cout<<"�ս����"<<zhongjiefu.size()<<"��"<<endl;
 set<char>::iterator zhong_it=zhongjiefu.begin();
 while(zhong_it!=zhongjiefu.end())
 {
  cout<<*zhong_it++<<' ';
 }
 cout<<endl;
 
}
void output_feizhongjiefu()
{
 cout<<"���ս����"<<feizhongjiefu.size()<<"��"<<endl;
 set<char>::iterator feizhong_it=feizhongjiefu.begin();
 while(feizhong_it!=feizhongjiefu.end())
 {
  cout<<*feizhong_it++<<' ';
 }
 cout<<endl;
}
void output_chanshengshi_num()
{
 cout<<"��Լʱ�Ĳ���ʽ��ţ�"<<endl;
 int num=1;
 vector<string>::iterator it=wenfa.begin();
 ++it;
 for(;it!=wenfa.end();++it,++num)
 {
  cout<<num<<'\t'<<*it<<endl;
 }
}
int main()
{
 inputwenfa("wenfa.txt");
 inputfirst("first.txt");
 findzhongjiefu();
 items();
 creat_goto();
 creat_action();
 
 output_zhuangtaitu();
 output_zhongjiefu();
 output_feizhongjiefu();
 output_chanshengshi_num();
 output_fenxibiao();
 


 system("pause");
 return 0;
}