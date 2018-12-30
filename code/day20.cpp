#include "days.h"
#include "util.h"

#include <algorithm>
#include <map>

struct Particle
{
  int id;
  bool dead;

  int64_t x;
  int64_t y;
  int64_t z;

  int64_t vx;
  int64_t vy;
  int64_t vz;

  int64_t ax;
  int64_t ay;
  int64_t az;

  uint64_t dist;

  bool operator <(const Particle &p) const
  {
    return dist < p.dist;
  }
};

void day20()
{
  printf("DAY 20\n");
  std::vector<char> input = readfile("../data/day20/input.txt");
  std::vector<std::string> lines = split(input, '\n');

  std::vector<Particle> particles;
  for(int i=0;i<lines.size();++i)
  {
    std::vector<std::string> parts = split(lines[i],' ');

    Particle p;
    p.id = i;
    p.dead = false;

    std::vector<std::string> subparts = split(parts[0].substr(3), ',');
    p.x = atoi(subparts[0].c_str());
    p.y = atoi(subparts[1].c_str());
    p.z = atoi(subparts[2].c_str());

    subparts = split(parts[1].substr(3), ',');
    p.vx = atoi(subparts[0].c_str());
    p.vy = atoi(subparts[1].c_str());
    p.vz = atoi(subparts[2].c_str());

    subparts = split(parts[2].substr(3), ',');
    p.ax = atoi(subparts[0].c_str());
    p.ay = atoi(subparts[1].c_str());
    p.az = atoi(subparts[2].c_str());

    particles.push_back(p);
  }

  for(int i=0;i<particles.size();++i)
  {
    Particle p = particles[i];
    printf("p=<%i,%i,%i>, v=<%i,%i,%i>, a=<%i,%i,%i>\n", p.x,p.y,p.z, p.vx,p.vy,p.vz, p.ax,p.ay,p.az);
  }

  int iterations = 4096;
  for(int i=0;i<iterations;++i)
  {
    std::map<std::string,int> collisions;

    for(int j=0;j<particles.size();++j)
    {
      Particle &p=particles[j];

      if(!p.dead)
      {
        p.vx+=p.ax;
        p.vy+=p.ay;
        p.vz+=p.az;

        p.x+=p.vx;
        p.y+=p.vy;
        p.z+=p.vz;

        p.dist = abs(p.x)+abs(p.y)+abs(p.z);

        char buf[256];
        sprintf(buf,"%i,%i,%i",p.x,p.y,p.z);

        auto k = collisions.find(std::string(buf));
        if(k!=collisions.end())
        {
          // annihilate both
          p.dead = true;
          particles[k->second].dead = true;
        }
        else
        {
          collisions.insert(std::pair<std::string,int>(std::string(buf), p.id));
        }
      }
      // scan collisions
    }
  }

  int alivecount=0;
  for(int j=0;j<particles.size();++j)
  {
    if(!particles[j].dead) alivecount++;
  }

  printf("%i\n", alivecount);

  std::sort(particles.begin(),particles.end());
  printf("%i\n", particles[0].id);

}
