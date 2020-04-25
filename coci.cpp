/*
 * https://gist.github.com/luciocf/542c123135cdbc433834c4b934978f4a
*/
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <bits/stdc++.h>
using namespace std;
#define sqr 547
#define mid (l+r)/2
#define pb push_back
#define ppb pop_back
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define era erase
#define C continue
#define mem(dp,i) memset(dp,i,sizeof(dp))
#define mset multiset
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef short int si;
typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pi> vpi;
typedef vector<pll> vpll;
const ll inf=1e18;
const ll mod=1e9+7;
const ld pai=acos(-1);
ll n , m ;
vll ord ;
vpll dag [100009] ;
vector < pair < pll , ll > > v [100009] ;
ll in [100009] , out [100009] , done [100009] , ans [100009] , dis [100009] ;
void init () {
	mem ( in , 0 ) ;
	mem ( out, 0 ) ;
	mem (done, 0 ) ;
	ord.clear () ;
	for ( int i = 0 ; i < n ; i ++ ) dag [i] .clear () ;
}
void dijkstra ( int st ) {
	for ( int i = 0 ; i < n ; i ++ ) dis [i] = 1e9 ;
	set < pll > s ;
	dis [st] = 0 ;
	s. ins ( { 0 , st } ) ;
	while ( s.size () ) {
		int node = s.begin()->se ;
		ll t = s.begin()->fi ;
		s .era ( s.begin() ) ;
		done [ node ] = 1 ;
		for ( auto U : v [node] ) {
			int u = U.fi.fi ;
			ll x = U.fi.se ;
			if ( done [u] ) C ;
			if ( s.count ( { dis[u] , u } ) ) s.era ( { dis[u] , u } ) ;
			dis [u] = min ( dis[u] , t+x ) ;
			s.ins ( { dis[u] , u } ) ;
		}
	}
}
void build () {
	for ( int u = 0 ; u < n ; u ++ ) {
		for ( auto i : v [u] ) {
			int v = i.fi.fi , x = i.fi.se , id = i.se ;
			if ( dis[u] + x == dis [v] ) {
				dag [u] .pb ( { v , id } ) ;
			}
		}
	}
}
void dfs ( int node ) {
	done [node] = 1 ;
	for ( auto u : dag[node] ) {
		if ( done [u.fi] ) C ;
		dfs ( u.fi ) ;
	}
	ord .pb ( node ) ;
}
int main () {
	scanf("%lld%lld",&n,&m);
	for ( int i = 0 ; i < m ; i ++ ) {
		int a , b , c ;
		cin >> a >> b >> c ;
		a -- , b -- ;
		v[a] .pb ( { { b , c } , i } ) ;
	}
	for ( int st = 0 ; st < n ; st ++ ) {
		init () ;
		dijkstra (st) ;
		build () ;
		mem ( done , 0 ) ;
		dfs ( st ) ;
		for ( auto u : ord ) {
			out [u] = 1 ;
			for ( auto v : dag [u] ) {
				out [u] += out [v.fi] ;
				out [u] %= mod ;
			}
		}
		reverse ( ord.begin() , ord.end() ) ;
		in [ st ] = 1 ;
		for ( auto u : ord ) {
			for ( auto v : dag[u] ) {
				in [v.fi] += in[u] ;
				in [v.fi] %= mod ;
			}
		}
		for ( int u = 0 ; u < n ; u ++ ) {
			for ( auto v : dag [u] ) {
				ans [ v.se ] += 1ll * in[u] * out [v.fi] ;
				ans [ v.se ] %= mod ;
			}
		}
	}
	for ( int i = 0 ; i < m ; i ++ ) printf("%lld\n",ans[i]) ;
}
