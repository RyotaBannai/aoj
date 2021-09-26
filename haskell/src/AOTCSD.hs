{-# OPTIONS_GHC -Wno-incomplete-patterns #-}

module AOTCSD where

type Stack = [Int]

type Areas = [(Int, Int)]

type State = (Stack, Areas, Pos)

type Pos = Int

type Accm = (Int, Int)

run :: String -> State -> Areas
run [] (_, a, _) = a
run inp@(x : xs) st@(sk, a, i)
  | x == '/' =
    let (xs', (sk', a', i'), (l, total)) = go inp st (i, 0)
     in run xs' (sk', (l, total) : a', i')
  | x == '\\' = run xs (i : sk, a, i + 1)
  | otherwise = run xs (sk, a, i + 1)
  where
    go :: String -> State -> Accm -> (String, State, Accm)
    go inp@(x : xs) ([], as, i) accm = (if x /= '/' then inp else xs, ([], as, if x /= '/' then i -1 else i), accm)
    go [] st accm = ([], st, accm)
    go inp@(x : xs) (sk, as, i) accm =
      if x /= '/'
        then (inp, (sk, as, if x /= '/' then i -1 else i), accm) -- return without consume `inp`
        else
          let pos = head sk
              dist = (-) i pos
              area = if (not . null $ as) && (fst . head $ as) > i then head as else (pos, 0)
              as' = if snd area /= 0 || null as then as else tail as
              total = dist + snd accm + snd area
           in go xs (tail sk, as', i + 1) (fst area, total)

test_inp :: [Char]
test_inp = ['\\', '\\', '/', '/']

test_inp2 :: [Char]
test_inp2 = ['\\', '\\', '/', '/', '/', '\\', '_', '/', '\\', '/', '\\', '\\', '\\', '\\', '/', '_', '/', '\\', '\\', '/', '/', '/', '_', '_', '\\', '\\', '\\', '_', '\\', '\\', '/', '_', '\\', '/', '_', '/', '\\']

main :: IO ()
main = do
  xs <- getLine
  print $ run test_inp2 ([], [], 1)